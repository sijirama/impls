# Tiled Matrix Multiplication: What the `m` Loop Really Does

## Overview

- **Topic:** A tiled CUDA matrix-multiplication kernel using shared memory
- **Audience:** A CUDA learner who understands threads, blocks, global memory, and `__syncthreads()` but cannot yet visualize the `m` loop
- **Example:** `Width = 8`, `TILE_WIDTH = 2`, four threads in `Block(0,0)`
- **Estimated length:** 3–4 minutes at a patient teaching pace
- **Key insight:** The block never changes. It repeatedly replaces the same small `Mds`/`Nds` buffers with the next 2×2 pair of tiles, synchronizes, reuses every loaded value, and accumulates the next two terms.

## Narrative arc

Start with the naive kernel so the viewer sees the entire row/column access. Then isolate the exact strips needed by `Block(0,0)`. The central sequence freezes the block and walks `m = 0, 1, 2, 3`: load eight values in parallel, wait, compute using only the shared tiles, wait again, and overwrite the same boxes. End by showing that all 16 blocks perform the same independent four-phase schedule.

## Scene 1: Naive baseline

**Duration:** ~25 seconds

**Purpose:** Establish that one output element requires eight products and that the naive approach repeatedly reaches into global-memory matrices.

### Visuals and content

- Display labelled 8×8 `Md`, `Nd`, and `Pd` grids.
- Outline `T(0,0)` and `Pd[0]`.
- Sweep across `Md` row 0 and down `Nd` column 0.
- Show the eight exact flat-array terms: `Md[0]×Nd[0]`, `Md[1]×Nd[8]`, …, `Md[7]×Nd[56]`.
- Keep the row/column highlights visible while the running expression changes.

### Teaching note

Say: “This is one thread, one output element, and eight global-memory pairs. There is no small reusable buffer yet.”

## Scene 2: What Block(0,0) owns

**Duration:** ~25 seconds

**Purpose:** Connect block coordinates to the strips of `Md` and `Nd` that are relevant to the output tile.

### Visuals and content

- Show `Pd` as a 4×4 arrangement of 2×2 block tiles and isolate `Block(0,0)`.
- Highlight `Md` rows 0–1 across all columns.
- Highlight `Nd` columns 0–1 across all rows.
- Divide the Md strip into four horizontal 2×2 chunks and the Nd strip into four vertical 2×2 chunks. Label both sequences `m=0`, `m=1`, `m=2`, `m=3`.
- Keep flat indices visible: Md chunks use rows `0–1` with columns `0–1`, `2–3`, `4–5`, `6–7`; Nd chunks use columns `0–1` with rows `0–1`, `2–3`, `4–5`, `6–7`.

### Teaching note

Say: “The block stays fixed. Only the pair of input chunks changes.”

## Scene 3: The phase loop

**Duration:** ~150 seconds

**Purpose:** Make the temporal reuse of the same shared-memory buffers unmistakable.

### Fixed layout

- Keep `Md`, `Nd`, and the four thread labels on screen.
- Keep one `Mds[2][2]` box and one `Nds[2][2]` box at fixed positions. Never replace them with new boxes.
- Keep a `Pvalue` accumulator visible throughout all four phases.

### Repeated phase beats

For each `m`:

1. **Load in parallel (~5 seconds):** Draw eight simultaneous arrows: each of the four threads sends one `Md` element and one `Nd` element into its corresponding `Mds` and `Nds` slot. Caption: “4 threads; 4 Md loads + 4 Nd loads; all at once.”
2. **First barrier (~4 seconds):** Animate all four thread markers reaching the same barrier and passing together. Explain that no thread may read shared memory until every write is complete.
3. **Compute and reuse (~12 seconds):** Keep the source grids dimmed. Highlight the two rows/columns inside `Mds` and `Nds` used by all four threads. Show `T(0,0)`’s two-term contribution and update `Pvalue`. Explicitly call out that the thread uses values loaded by its neighbors.
4. **Second barrier and overwrite (~6 seconds):** Synchronize again, wipe the contents of the same shared boxes, and refill them with the next phase color. The block and boxes remain in place while only the data changes.

### Exact `T(0,0)` terms

- `m=0`: `Md[0]×Nd[0] + Md[1]×Nd[8]`
- `m=1`: `Md[2]×Nd[16] + Md[3]×Nd[24]`
- `m=2`: `Md[4]×Nd[32] + Md[5]×Nd[40]`
- `m=3`: `Md[6]×Nd[48] + Md[7]×Nd[56]`

### Teaching note

Repeat the mantra: “Same block. Same shared boxes. New chunk. Synchronize. Reuse.”

## Scene 4: Finish and zoom out

**Duration:** ~25 seconds

**Purpose:** Connect the one-block story to the complete grid launch.

### Visuals and content

- Show the final eight-term `Pvalue` expression and write it to `Pd[0]`.
- Zoom out to the 4×4 block grid.
- Compare `Block(0,0)` and `Block(1,0)`: both use `Md` rows 0–1, but the latter uses `Nd` columns 2–3.
- End with: “Every block performs the same four-phase dance independently and in parallel.”

## Color palette

- **Amber:** Md data and Md chunks
- **Purple:** Nd data and Nd chunks
- **Green:** Pd/output ownership
- **Red:** threads and synchronization barriers
- **Phase colors:** amber, purple, green, blue for the four changing chunk identities
- **Background:** dark neutral for high contrast

## Implementation notes

- Use `Text` rather than LaTeX for CUDA identifiers so the animation does not require a LaTeX installation.
- Use `AnimationGroup(..., lag_ratio=0)` for genuinely parallel transfers.
- Use `Transform` for the changing phase captions and accumulator so the viewer sees continuity.
- Use explicit flat indices in every input-cell label; never show an unlabelled colored square as the only representation of a matrix value.
