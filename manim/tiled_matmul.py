from manim import *


WIDTH = 8
TILE_WIDTH = 2
CELL = 0.34

AMBER = "#F4B942"
PURPLE = "#A78BFA"
GREEN = "#55C271"
BLUE = "#4EA5D9"
PHASE_COLORS = [AMBER, PURPLE, GREEN, BLUE]


def label(text, size=24, color=WHITE):
    return Text(text, font_size=size, color=color)


def matrix_grid(name, x, y, cell_size=CELL, labels=True, accent=BLUE):
    """Create a labelled 8x8 matrix. Cell labels are flat-array indices."""
    group = VGroup()
    title = label(name, 25, accent).move_to([x, y + 1.72, 0])
    group.add(title)
    for row in range(WIDTH):
        for col in range(WIDTH):
            rect = Square(side_length=cell_size, stroke_width=1.2)
            rect.set_fill(BLACK, opacity=0.08)
            rect.move_to([x + (col - 3.5) * cell_size, y - (row - 3.5) * cell_size, 0])
            if labels:
                index = row * WIDTH + col
                cell_label = label(f"{name}[{index}]", 8, WHITE).move_to(rect.get_center())
                group.add(VGroup(rect, cell_label))
            else:
                group.add(rect)
    return group


def cell_center(x, y, row, col, cell_size=CELL):
    return np.array([x + (col - 3.5) * cell_size, y - (row - 3.5) * cell_size, 0])


def highlight_cell(x, y, row, col, color, cell_size=CELL, width=0.34):
    box = Square(side_length=cell_size, stroke_color=color, stroke_width=width)
    box.set_fill(color, opacity=0.32)
    box.move_to(cell_center(x, y, row, col, cell_size))
    return box


def shared_tile(name, x, y, cell_size=0.72):
    group = VGroup()
    title = label(name, 22, WHITE).move_to([x, y + 1.12, 0])
    group.add(title)
    for row in range(2):
        for col in range(2):
            rect = Square(side_length=cell_size, stroke_width=2)
            rect.set_fill(BLACK, opacity=0.1)
            rect.move_to([x + (col - 0.5) * cell_size, y - (row - 0.5) * cell_size, 0])
            group.add(rect)
    return group


class TiledMatrixMultiplication(Scene):
    def construct(self):
        self.scene_one_naive()
        self.scene_two_territory()
        self.scene_three_phases()
        self.scene_four_parallel_blocks()

    def caption(self, text, color=WHITE, size=22):
        cap = label(text, size, color).to_edge(DOWN, buff=0.22)
        self.play(FadeIn(cap), run_time=0.35)
        return cap

    def scene_one_naive(self):
        title = label("1. Naive matrix multiplication", 32, WHITE).to_edge(UP, buff=0.25)
        md = matrix_grid("Md", -4.35, 1.05, accent=AMBER)
        nd = matrix_grid("Nd", 0.0, 1.05, accent=PURPLE)
        pd = matrix_grid("Pd", 4.35, -2.35, accent=GREEN)
        self.play(Write(title), FadeIn(md), FadeIn(nd), FadeIn(pd), run_time=1.4)

        thread = label("T(0,0) computes Pd[0]", 20, RED).next_to(pd, UP, buff=0.18)
        md_row = VGroup(*[
            highlight_cell(-4.35, 1.05, 0, col, AMBER) for col in range(8)
        ])
        nd_col = VGroup(*[
            highlight_cell(0.0, 1.05, row, 0, PURPLE) for row in range(8)
        ])
        self.play(FadeIn(thread), Create(md_row), Create(nd_col), run_time=1.0)

        formula = label("Pvalue += Md[0] * Nd[0]", 22, YELLOW).to_edge(DOWN, buff=0.65)
        self.play(FadeIn(formula), run_time=0.4)
        for k in range(8):
            left = cell_center(-4.35, 1.05, 0, k)
            right = cell_center(0.0, 1.05, k, 0)
            a = Arrow(left, left + RIGHT * 0.25, buff=0.02, color=AMBER, stroke_width=3)
            b = Arrow(right, right + DOWN * 0.25, buff=0.02, color=PURPLE, stroke_width=3)
            next_formula = label(
                f"Pvalue += Md[{k}] * Nd[{k * WIDTH}]", 22, YELLOW
            ).to_edge(DOWN, buff=0.65)
            self.play(
                Create(a), Create(b),
                Transform(formula, next_formula),
                run_time=0.42,
            )
            self.remove(a, b)

        result = highlight_cell(4.35, -2.35, 0, 0, GREEN, width=0.35)
        result_text = label("Pd[0] filled", 18, GREEN).next_to(result, RIGHT, buff=0.1)
        self.play(Create(result), FadeIn(result_text), run_time=0.6)
        cap = self.caption("Naive: full row + full column fetched directly from global memory")
        self.wait(1.0)
        self.play(FadeOut(VGroup(title, md, nd, pd, thread, md_row, nd_col, formula, result, result_text, cap)))

    def scene_two_territory(self):
        title = label("2. Block(0,0)'s territory", 32, WHITE).to_edge(UP, buff=0.25)
        md = matrix_grid("Md", -4.35, 1.0, accent=AMBER)
        nd = matrix_grid("Nd", 0.0, 1.0, accent=PURPLE)
        self.play(Write(title), FadeIn(md), FadeIn(nd), run_time=1.0)

        md_band = SurroundingRectangle(
            VGroup(*[md[1 + row * 8 + col] for row in range(2) for col in range(8)]),
            color=AMBER, buff=0.04, stroke_width=4
        )
        nd_band = SurroundingRectangle(
            VGroup(*[nd[1 + row * 8 + col] for row in range(8) for col in range(2)]),
            color=PURPLE, buff=0.04, stroke_width=4
        )
        self.play(Create(md_band), Create(nd_band), run_time=0.9)
        cap = self.caption("Block(0,0) only needs rows 0-1 of Md and columns 0-1 of Nd")
        self.wait(1.2)
        self.play(FadeOut(cap))

        chunk_labels = VGroup()
        for m, color in enumerate(PHASE_COLORS):
            md_chunk = SurroundingRectangle(
                VGroup(*[md[1 + row * 8 + col] for row in range(2) for col in range(m * 2, m * 2 + 2)]),
                color=color, buff=0.025, stroke_width=3
            )
            nd_chunk = SurroundingRectangle(
                VGroup(*[nd[1 + row * 8 + col] for row in range(8) for col in range(m * 2, m * 2 + 2)]),
                color=color, buff=0.025, stroke_width=3
            )
            chunk_labels.add(md_chunk, nd_chunk)
            m_label = label(f"m={m}", 18, color).move_to(md_chunk.get_top() + UP * 0.18)
            n_label = label(f"m={m}", 18, color).move_to(nd_chunk.get_top() + UP * 0.18)
            chunk_labels.add(m_label, n_label)
        self.play(Create(chunk_labels), run_time=1.6)
        cap = self.caption("The strip is walked in 4 chunks: m=0, m=1, m=2, m=3")
        self.wait(1.3)
        self.play(FadeOut(VGroup(title, md, nd, md_band, nd_band, chunk_labels, cap)))

    def thread_icons(self, x, y):
        names = ["T(0,0)", "T(1,0)", "T(0,1)", "T(1,1)"]
        positions = [
            [x - 1.6, y + 1.25, 0], [x - 0.3, y + 1.25, 0],
            [x - 1.6, y - 1.1, 0], [x - 0.3, y - 1.1, 0],
        ]
        return VGroup(*[
            VGroup(Dot(pos, radius=0.09, color=RED), label(name, 14).next_to(pos, DOWN, buff=0.08))
            for name, pos in zip(names, positions)
        ])

    def scene_three_phases(self):
        title = label("3. The m loop: same block, changing data chunk", 30, WHITE).to_edge(UP, buff=0.2)
        md = matrix_grid("Md", -4.35, 1.0, accent=AMBER)
        nd = matrix_grid("Nd", 0.0, 1.0, accent=PURPLE)
        self.play(Write(title), FadeIn(md), FadeIn(nd), run_time=1.0)

        mds = shared_tile("Mds", 3.55, 1.35)
        nds = shared_tile("Nds", 3.55, -1.35)
        shared = VGroup(mds, nds)
        self.play(FadeIn(shared), run_time=0.7)

        blocks = self.thread_icons(-0.1, -2.8)
        self.play(FadeIn(blocks), run_time=0.5)

        pvalue = label("Pvalue = 0", 20, YELLOW).to_edge(DOWN, buff=0.35)
        self.play(FadeIn(pvalue), run_time=0.3)

        for m, color in enumerate(PHASE_COLORS):
            self.run_phase(m, color, md, nd, mds, nds, blocks, pvalue)

        final = label(
            "Pvalue = Md[0]×Nd[0] + Md[1]×Nd[8] + Md[2]×Nd[16] + Md[3]×Nd[24]"
            " + Md[4]×Nd[32] + Md[5]×Nd[40] + Md[6]×Nd[48] + Md[7]×Nd[56]",
            15, YELLOW
        ).to_edge(DOWN, buff=0.33)
        self.play(Transform(pvalue, final), run_time=1.0)
        pd_box = Square(side_length=0.7, color=GREEN, stroke_width=4).move_to([5.4, -2.7, 0])
        pd_text = label("Pd[0]", 20, GREEN).move_to(pd_box)
        write_arrow = Arrow(pvalue.get_right(), pd_box.get_left(), color=GREEN, buff=0.1)
        self.play(Create(write_arrow), Create(pd_box), FadeIn(pd_text), run_time=0.8)
        cap = self.caption("4 phases later: same 8 terms as naive, but only one 2×2 tile lives in shared memory")
        self.wait(1.8)
        self.play(FadeOut(VGroup(title, md, nd, shared, blocks, pvalue, pd_box, pd_text, write_arrow, cap)))

    def run_phase(self, m, color, md, nd, mds, nds, blocks, pvalue):
        phase = label(f"Phase m={m}", 24, color).to_edge(UP, buff=0.75)
        chunk_md = SurroundingRectangle(
            VGroup(*[md[1 + row * 8 + col] for row in range(2) for col in range(m * 2, m * 2 + 2)]),
            color=color, buff=0.02, stroke_width=4
        )
        chunk_nd = SurroundingRectangle(
            VGroup(*[nd[1 + row * 8 + col] for row in range(8) for col in range(m * 2, m * 2 + 2)]),
            color=color, buff=0.02, stroke_width=4
        )
        instruction = label("4 threads: 4 Md loads + 4 Nd loads, simultaneously", 18, color).to_edge(DOWN, buff=0.35)
        self.play(FadeIn(phase), Create(chunk_md), Create(chunk_nd), Transform(pvalue, instruction), run_time=0.7)

        # All four arrows are created in one AnimationGroup: the loads are parallel.
        source_positions = [
            cell_center(-4.35, 1.0, row, m * 2 + col)
            for row in range(2) for col in range(2)
        ] + [
            cell_center(0.0, 1.0, m * 2 + row, col)
            for row in range(2) for col in range(2)
        ]
        target_positions = [
            mds[1 + row * 2 + col].get_center()
            for row in range(2) for col in range(2)
        ] + [
            nds[1 + row * 2 + col].get_center()
            for row in range(2) for col in range(2)
        ]
        arrows = VGroup(*[
            Arrow(source, target, color=color, buff=0.08, stroke_width=3)
            for source, target in zip(source_positions, target_positions)
        ])
        tile_fills = VGroup(*[
            Square(side_length=0.68, color=color, fill_color=color, fill_opacity=0.55, stroke_width=2).move_to(pos)
            for pos in target_positions
        ])
        load_text = label("each thread loads ONE Md element and ONE Nd element", 17, color).to_edge(DOWN, buff=0.35)
        self.play(AnimationGroup(*[Create(a) for a in arrows], lag_ratio=0), run_time=0.8)
        self.play(AnimationGroup(*[FadeIn(s) for s in tile_fills], lag_ratio=0), Transform(pvalue, load_text), run_time=0.5)
        self.remove(arrows)

        barrier = Line([-1.8, -1.95, 0], [1.8, -1.95, 0], color=RED, stroke_width=5)
        barrier_text = label("__syncthreads() — wait for ALL 4 loads", 17, RED).next_to(barrier, DOWN, buff=0.12)
        self.play(Create(barrier), FadeIn(barrier_text), run_time=0.5)
        self.play(AnimationGroup(*[blocks[i].animate.shift(DOWN * 0.25) for i in range(4)], lag_ratio=0), run_time=0.35)
        self.play(AnimationGroup(*[blocks[i].animate.shift(UP * 0.25) for i in range(4)], lag_ratio=0), run_time=0.35)
        self.play(FadeOut(VGroup(barrier, barrier_text)), run_time=0.3)

        terms = [
            f"Md[{m * 2}]×Nd[{m * 16}] + Md[{m * 2 + 1}]×Nd[{m * 16 + 8}]",
            f"Md[{m * 2 + 1}]×Nd[{m * 16 + 1}] + Md[{m * 2 + 2}]×Nd[{m * 16 + 9}]",
        ]
        compute = label("All 4 threads read the WHOLE 2×2 tile", 17, color).to_edge(DOWN, buff=0.35)
        self.play(Transform(pvalue, compute), run_time=0.45)
        reuse = label(f"T(0,0): Pvalue += {terms[0]}", 16, YELLOW).to_edge(DOWN, buff=0.35)
        self.play(Transform(pvalue, reuse), run_time=0.65)

        barrier = Line([-1.8, -1.95, 0], [1.8, -1.95, 0], color=RED, stroke_width=5)
        barrier_text = label("__syncthreads() — finish reading before overwrite", 16, RED).next_to(barrier, DOWN, buff=0.12)
        self.play(Create(barrier), FadeIn(barrier_text), run_time=0.45)
        self.play(AnimationGroup(*[blocks[i].animate.shift(DOWN * 0.2) for i in range(4)], lag_ratio=0), run_time=0.3)
        self.play(AnimationGroup(*[blocks[i].animate.shift(UP * 0.2) for i in range(4)], lag_ratio=0), run_time=0.3)
        self.play(FadeOut(VGroup(barrier, barrier_text)), run_time=0.25)

        if m < 3:
            wipe = AnimationGroup(
                *[tile.animate.set_fill(BLACK, opacity=0.05) for tile in tile_fills],
                lag_ratio=0,
            )
            self.play(wipe, FadeOut(VGroup(phase, chunk_md, chunk_nd)), run_time=0.55)
        else:
            self.play(FadeOut(VGroup(phase, chunk_md, chunk_nd, tile_fills)), run_time=0.55)

    def scene_four_parallel_blocks(self):
        title = label("4. Every block performs the same dance in parallel", 30, WHITE).to_edge(UP, buff=0.25)
        grid = VGroup()
        origin = np.array([-1.6, 0.1, 0])
        size = 0.52
        for by in range(4):
            for bx in range(4):
                rect = Square(side_length=size, stroke_width=1.5)
                rect.set_fill(PHASE_COLORS[(bx + by) % 4], opacity=0.45)
                rect.move_to(origin + np.array([bx * size, -by * size, 0]))
                grid.add(rect)
        grid_label = label("Pd: 4×4 blocks, each block = 2×2 threads", 20, GREEN).next_to(grid, DOWN, buff=0.25)
        b00 = SurroundingRectangle(grid[0], color=RED, stroke_width=4, buff=0.03)
        b10 = SurroundingRectangle(grid[4], color=YELLOW, stroke_width=4, buff=0.03)
        b00_text = label("Block(0,0)", 17, RED).next_to(b00, LEFT, buff=0.15)
        b10_text = label("Block(1,0)", 17, YELLOW).next_to(b10, LEFT, buff=0.15)
        self.play(Write(title), Create(grid), FadeIn(grid_label), Create(b00), Create(b10), FadeIn(b00_text), FadeIn(b10_text), run_time=1.4)

        md = matrix_grid("Md", -4.25, 1.4, cell_size=0.28, accent=AMBER)
        nd = matrix_grid("Nd", 3.9, 1.4, cell_size=0.28, accent=PURPLE)
        md_strip = SurroundingRectangle(
            VGroup(*[md[1 + row * 8 + col] for row in range(2) for col in range(8)]),
            color=RED, buff=0.02, stroke_width=4
        )
        nd00_strip = SurroundingRectangle(
            VGroup(*[nd[1 + row * 8 + col] for row in range(8) for col in range(2)]),
            color=RED, buff=0.02, stroke_width=4
        )
        nd10_strip = SurroundingRectangle(
            VGroup(*[nd[1 + row * 8 + col] for row in range(8) for col in range(2, 4)]),
            color=YELLOW, buff=0.02, stroke_width=4
        )
        text = label("Block(0,0): Md rows 0-1 + Nd cols 0-1", 17, RED).to_edge(DOWN, buff=0.55)
        text2 = label("Block(1,0): same Md rows 0-1 + Nd cols 2-3", 17, YELLOW).to_edge(DOWN, buff=0.25)
        self.play(FadeIn(md), FadeIn(nd), Create(md_strip), Create(nd00_strip), Create(nd10_strip), FadeIn(text), FadeIn(text2), run_time=1.2)
        cap = self.caption("The BLOCK stays the same; the DATA CHUNK changes. Every block repeats the 4-phase dance independently.", size=19)
        self.wait(2.0)
        self.play(FadeOut(VGroup(title, grid, grid_label, b00, b10, b00_text, b10_text, md, nd, md_strip, nd00_strip, nd10_strip, text, text2, cap)))


if __name__ == "__main__":
    scene = TiledMatrixMultiplication
