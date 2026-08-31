from manim import *


WIDTH = 8
TILE = 2
CELL = 0.34
AMBER = "#F4B942"
PURPLE = "#A78BFA"
GREEN = "#55C271"
BLUE = "#4EA5D9"
RED = "#FF6B6B"
PHASE = [AMBER, PURPLE, GREEN, BLUE]


def txt(value, size=24, color=WHITE):
    return Text(value, font_size=size, color=color)


def grid8(name, center, cell=CELL, title_color=WHITE, font_size=8):
    """Return a labelled 8x8 flat-array matrix and its cell objects."""
    group = VGroup()
    title = txt(name, 24, title_color).move_to(center + UP * (4 * cell + 0.35))
    group.add(title)
    cells = []
    for row in range(8):
        for col in range(8):
            square = Square(side_length=cell, stroke_width=1.2)
            square.set_fill(BLACK, opacity=0.08)
            square.move_to(center + RIGHT * (col - 3.5) * cell + DOWN * (row - 3.5) * cell)
            number = txt(f"{name}[{row * 8 + col}]", font_size, WHITE).move_to(square)
            cell_group = VGroup(square, number)
            cells.append(cell_group)
            group.add(cell_group)
    return group, cells


def center8(center, row, col, cell=CELL):
    return center + RIGHT * (col - 3.5) * cell + DOWN * (row - 3.5) * cell


def outline(center, row, col, color, cell=CELL, width=3):
    box = Square(side_length=cell, stroke_color=color, stroke_width=width)
    box.set_fill(color, opacity=0.3)
    return box.move_to(center8(center, row, col, cell))


def tile_box(name, center, color=WHITE, cell=0.7):
    title = txt(name, 23, color).move_to(center + UP * (cell + 0.38))
    squares = []
    for row in range(2):
        for col in range(2):
            square = Square(side_length=cell, stroke_color=color, stroke_width=2)
            square.set_fill(BLACK, opacity=0.12)
            square.move_to(center + RIGHT * (col - 0.5) * cell + DOWN * (row - 0.5) * cell)
            squares.append(square)
    return VGroup(title, *squares), squares


def tile_center(center, row, col, cell=0.7):
    return center + RIGHT * (col - 0.5) * cell + DOWN * (row - 0.5) * cell


class TiledMatrixMultiplicationDetailed(Scene):
    def construct(self):
        self.camera.background_color = "#10131A"
        self.naive_baseline()
        self.block_territory()
        self.phase_loop()
        self.parallel_blocks()

    def bottom_caption(self, value, color=WHITE, size=22):
        caption = txt(value, size, color).to_edge(DOWN, buff=0.18)
        self.play(FadeIn(caption), run_time=0.4)
        return caption

    def naive_baseline(self):
        title = txt("Tiled matrix multiplication: first, the naive view", 31).to_edge(UP, buff=0.2)
        md, md_cells = grid8("Md", np.array([-4.25, 1.0, 0]), title_color=AMBER)
        nd, nd_cells = grid8("Nd", np.array([0.0, 1.0, 0]), title_color=PURPLE)
        pd, pd_cells = grid8("Pd", np.array([4.25, -2.65, 0]), title_color=GREEN)
        self.play(Write(title), FadeIn(md), FadeIn(nd), FadeIn(pd), run_time=1.8)

        thread = txt("T(0,0) owns Pd[0]", 21, RED).next_to(pd, UP, buff=0.08)
        row = VGroup(*[outline(np.array([-4.25, 1.0, 0]), 0, col, AMBER) for col in range(8)])
        column = VGroup(*[outline(np.array([0.0, 1.0, 0]), row_index, 0, PURPLE) for row_index in range(8)])
        self.play(FadeIn(thread), Create(row), Create(column), run_time=1.0)

        formula = txt("Pvalue = 0", 20, YELLOW).to_edge(DOWN, buff=0.55)
        self.play(FadeIn(formula), run_time=0.4)
        md_center = np.array([-4.25, 1.0, 0])
        nd_center = np.array([0.0, 1.0, 0])
        for k in range(8):
            next_formula = txt(
                f"Pvalue += Md[{k}] × Nd[{k * 8}]", 20, YELLOW
            ).to_edge(DOWN, buff=0.55)
            md_arrow = Arrow(center8(md_center, 0, k), center8(md_center, 0, k) + RIGHT * 0.2, color=AMBER, buff=0.02)
            nd_arrow = Arrow(center8(nd_center, k, 0), center8(nd_center, k, 0) + DOWN * 0.2, color=PURPLE, buff=0.02)
            self.play(Create(md_arrow), Create(nd_arrow), Transform(formula, next_formula), run_time=0.45)
            self.remove(md_arrow, nd_arrow)
        result = outline(np.array([4.25, -2.65, 0]), 0, 0, GREEN, width=4)
        self.play(Create(result), run_time=0.45)
        caption = self.bottom_caption("Naive: one thread walks a full row and a full column in global memory")
        self.wait(1.4)
        self.play(FadeOut(VGroup(title, md, nd, pd, thread, row, column, formula, result, caption)), run_time=0.8)

    def block_territory(self):
        title = txt("Block(0,0): which data does this block need?", 31).to_edge(UP, buff=0.2)
        md_center = np.array([-4.25, 1.0, 0])
        nd_center = np.array([0.0, 1.0, 0])
        md, md_cells = grid8("Md", md_center, title_color=AMBER)
        nd, nd_cells = grid8("Nd", nd_center, title_color=PURPLE)
        self.play(Write(title), FadeIn(md), FadeIn(nd), run_time=1.4)

        md_band = SurroundingRectangle(VGroup(*md_cells[:16]), color=AMBER, buff=0.03, stroke_width=4)
        nd_band = SurroundingRectangle(VGroup(*[nd_cells[row * 8 + col] for row in range(8) for col in range(2)]), color=PURPLE, buff=0.03, stroke_width=4)
        band_text = txt("Md rows 0–1", 19, AMBER).next_to(md_band, DOWN, buff=0.12)
        band_text2 = txt("Nd columns 0–1", 19, PURPLE).next_to(nd_band, DOWN, buff=0.12)
        self.play(Create(md_band), Create(nd_band), FadeIn(band_text), FadeIn(band_text2), run_time=1.0)
        caption = self.bottom_caption("Block(0,0) owns Pd[0..1][0..1], so it needs two strips—not the whole matrices")
        self.wait(1.4)
        self.play(FadeOut(caption), run_time=0.4)

        chunks = VGroup()
        for m, color in enumerate(PHASE):
            md_chunk = SurroundingRectangle(
                VGroup(*[md_cells[row * 8 + col] for row in range(2) for col in range(m * 2, m * 2 + 2)]),
                color=color, buff=0.015, stroke_width=3
            )
            nd_chunk = SurroundingRectangle(
                VGroup(*[nd_cells[row * 8 + col] for row in range(m * 2, m * 2 + 2) for col in range(2)]),
                color=color, buff=0.015, stroke_width=3
            )
            chunks.add(md_chunk, nd_chunk)
            chunks.add(txt(f"m={m}", 16, color).move_to(md_chunk.get_top() + UP * 0.18))
            chunks.add(txt(f"m={m}", 16, color).move_to(nd_chunk.get_top() + UP * 0.18))
        self.play(Create(chunks), run_time=1.8)
        caption = self.bottom_caption("Width / TILE_WIDTH = 8 / 2 = 4 phases: the strips are consumed in 2×2 chunks")
        self.wait(1.4)
        self.play(FadeOut(VGroup(title, md, nd, md_band, nd_band, band_text, band_text2, chunks, caption)), run_time=0.8)

    def phase_loop(self):
        title = txt("The phase loop: same block, same boxes, new data", 31).to_edge(UP, buff=0.2)
        md_center = np.array([-4.55, 1.05, 0])
        nd_center = np.array([-0.15, 1.05, 0])
        md, md_cells = grid8("Md", md_center, cell=0.28, title_color=AMBER, font_size=7)
        nd, nd_cells = grid8("Nd", nd_center, cell=0.28, title_color=PURPLE, font_size=7)
        mds_center = np.array([3.25, 1.5, 0])
        nds_center = np.array([3.25, -1.05, 0])
        mds, mds_squares = tile_box("Mds[2][2]", mds_center, AMBER, 0.68)
        nds, nds_squares = tile_box("Nds[2][2]", nds_center, PURPLE, 0.68)
        self.play(Write(title), FadeIn(md), FadeIn(nd), FadeIn(mds), FadeIn(nds), run_time=1.4)

        fixed = txt("Block(0,0)   |   4 threads: T(0,0)  T(1,0)  T(0,1)  T(1,1)", 17, RED).to_edge(DOWN, buff=0.52)
        self.play(FadeIn(fixed), run_time=0.4)
        pvalue = txt("Pvalue = 0", 20, YELLOW).to_edge(DOWN, buff=0.18)
        self.play(FadeIn(pvalue), run_time=0.4)

        for m, color in enumerate(PHASE):
            self.one_phase(m, color, md_center, nd_center, md_cells, nd_cells, mds_squares, nds_squares, pvalue)

        total = txt(
            "Pvalue = Md[0]×Nd[0] + Md[1]×Nd[8] + Md[2]×Nd[16] + Md[3]×Nd[24]"
            " + Md[4]×Nd[32] + Md[5]×Nd[40] + Md[6]×Nd[48] + Md[7]×Nd[56]",
            14, YELLOW
        ).to_edge(DOWN, buff=0.18)
        self.play(Transform(pvalue, total), run_time=1.0)
        output = Square(side_length=0.72, stroke_color=GREEN, stroke_width=4).move_to([5.65, -1.1, 0])
        output_label = txt("Pd[0]", 18, GREEN).move_to(output)
        arrow = Arrow(pvalue.get_right(), output.get_left(), color=GREEN, buff=0.1)
        self.play(Create(arrow), Create(output), FadeIn(output_label), run_time=0.8)
        caption = self.bottom_caption("After 4 phases: 8 products are complete, but shared memory held only 2×2 values at a time", GREEN, 20)
        self.wait(2.0)
        self.play(FadeOut(VGroup(title, md, nd, mds, nds, fixed, pvalue, output, output_label, arrow, caption)), run_time=0.8)

    def one_phase(self, m, color, md_center, nd_center, md_cells, nd_cells, mds_squares, nds_squares, pvalue):
        phase = txt(f"m={m}: BLOCK stays fixed; DATA CHUNK changes", 22, color).to_edge(UP, buff=0.72)
        md_focus = SurroundingRectangle(VGroup(*[md_cells[row * 8 + col] for row in range(2) for col in range(m * 2, m * 2 + 2)]), color=color, buff=0.015, stroke_width=4)
        nd_focus = SurroundingRectangle(VGroup(*[nd_cells[row * 8 + col] for row in range(m * 2, m * 2 + 2) for col in range(2)]), color=color, buff=0.015, stroke_width=4)
        load_caption = txt("LOAD: each thread sends one Md value and one Nd value", 18, color).to_edge(DOWN, buff=0.18)
        self.play(FadeIn(phase), Create(md_focus), Create(nd_focus), Transform(pvalue, load_caption), run_time=0.7)

        # Correct flat indexing for Block(0,0): each (tx, ty) loads two values.
        md_sources = [
            center8(md_center, ty, m * 2 + tx, 0.28)
            for ty in range(2) for tx in range(2)
        ]
        nd_sources = [
            center8(nd_center, m * 2 + ty, tx, 0.28)
            for ty in range(2) for tx in range(2)
        ]
        targets = [
            tile_center(np.array([3.25, 1.5, 0]), ty, tx)
            for ty in range(2) for tx in range(2)
        ] + [
            tile_center(np.array([3.25, -1.05, 0]), ty, tx)
            for ty in range(2) for tx in range(2)
        ]
        arrows = VGroup(*[
            Arrow(source, target, color=color, buff=0.06, stroke_width=2.5)
            for source, target in zip(md_sources + nd_sources, targets)
        ])
        fills = VGroup(*[
            Square(side_length=0.63, stroke_color=color, fill_color=color, fill_opacity=0.55, stroke_width=2).move_to(target)
            for target in targets
        ])
        self.play(AnimationGroup(*[Create(arrow) for arrow in arrows], lag_ratio=0), run_time=1.1)
        self.play(AnimationGroup(*[FadeIn(fill) for fill in fills], lag_ratio=0), run_time=0.7)
        self.remove(arrows)
        self.wait(0.8)

        barrier = Line([-1.6, -1.75, 0], [2.0, -1.75, 0], color=RED, stroke_width=5)
        barrier_text = txt("__syncthreads(): all 4 threads wait here", 17, RED).next_to(barrier, DOWN, buff=0.08)
        self.play(Create(barrier), FadeIn(barrier_text), run_time=0.65)
        self.wait(0.6)
        self.play(FadeOut(VGroup(barrier, barrier_text)), run_time=0.35)

        compute_caption = txt("COMPUTE: every thread reads the whole 2×2 shared tile", 18, color).to_edge(DOWN, buff=0.18)
        self.play(Transform(pvalue, compute_caption), run_time=0.55)
        terms = f"T(0,0): + Md[{m * 2}]×Nd[{m * 16}] + Md[{m * 2 + 1}]×Nd[{m * 16 + 8}]"
        compute = txt(terms, 16, YELLOW).to_edge(DOWN, buff=0.18)
        self.play(Transform(pvalue, compute), run_time=0.8)
        reuse = txt("Reuse: T(0,0) reads values loaded by T(1,0), T(0,1), and T(1,1)", 16, GREEN).to_edge(DOWN, buff=0.18)
        self.play(Transform(pvalue, reuse), run_time=0.75)
        self.wait(1.0)

        barrier = Line([-1.6, -1.75, 0], [2.0, -1.75, 0], color=RED, stroke_width=5)
        barrier_text = txt("__syncthreads(): finish reading before overwrite", 17, RED).next_to(barrier, DOWN, buff=0.08)
        self.play(Create(barrier), FadeIn(barrier_text), run_time=0.65)
        self.wait(0.6)
        self.play(FadeOut(VGroup(barrier, barrier_text)), run_time=0.35)
        if m < 3:
            clear = AnimationGroup(*[fill.animate.set_fill(BLACK, opacity=0.05) for fill in fills], lag_ratio=0)
            self.play(clear, FadeOut(VGroup(phase, md_focus, nd_focus)), run_time=0.75)
        else:
            self.play(FadeOut(VGroup(phase, md_focus, nd_focus, fills)), run_time=0.75)

    def parallel_blocks(self):
        title = txt("Zoom out: every block performs the same dance", 31).to_edge(UP, buff=0.2)
        origin = np.array([-1.45, 1.3, 0])
        size = 0.68
        blocks = VGroup()
        for by in range(4):
            for bx in range(4):
                block = Square(side_length=size, stroke_width=2, stroke_color=WHITE)
                block.set_fill(PHASE[(bx + by) % 4], opacity=0.45)
                block.move_to(origin + RIGHT * bx * size + DOWN * by * size)
                blocks.add(block)
        grid_label = txt("Pd = 8×8, so blocksPerGrid = 8 / 2 = 4 in each direction", 19, GREEN).next_to(blocks, DOWN, buff=0.25)
        b00 = SurroundingRectangle(blocks[0], color=RED, stroke_width=4, buff=0.03)
        b10 = SurroundingRectangle(blocks[4], color=YELLOW, stroke_width=4, buff=0.03)
        self.play(Write(title), Create(blocks), FadeIn(grid_label), Create(b00), Create(b10), run_time=1.5)

        md_center = np.array([-4.5, -1.0, 0])
        nd_center = np.array([3.9, -1.0, 0])
        md, md_cells = grid8("Md", md_center, cell=0.22, title_color=AMBER, font_size=6)
        nd, nd_cells = grid8("Nd", nd_center, cell=0.22, title_color=PURPLE, font_size=6)
        md_strip = SurroundingRectangle(VGroup(*md_cells[:16]), color=RED, buff=0.015, stroke_width=3)
        nd00 = SurroundingRectangle(VGroup(*[nd_cells[row * 8 + col] for row in range(8) for col in range(2)]), color=RED, buff=0.015, stroke_width=3)
        nd10 = SurroundingRectangle(VGroup(*[nd_cells[row * 8 + col] for row in range(8) for col in range(2, 4)]), color=YELLOW, buff=0.015, stroke_width=3)
        t1 = txt("Block(0,0): Md rows 0–1 + Nd cols 0–1", 16, RED).to_edge(DOWN, buff=0.48)
        t2 = txt("Block(1,0): Md rows 0–1 + Nd cols 2–3", 16, YELLOW).to_edge(DOWN, buff=0.2)
        self.play(FadeIn(md), FadeIn(nd), Create(md_strip), Create(nd00), Create(nd10), FadeIn(t1), FadeIn(t2), run_time=1.3)
        caption = self.bottom_caption("All 16 blocks repeat the four phases independently and in parallel", size=21)
        self.wait(2.2)
        self.play(FadeOut(VGroup(title, blocks, grid_label, b00, b10, md, nd, md_strip, nd00, nd10, t1, t2, caption)), run_time=0.8)


if __name__ == "__main__":
    pass
