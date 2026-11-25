#!/usr/bin/env python3
"""Прогоняет настоящие бинарники и складывает реальный вывод в assets/term.json.

Отчёт рисует из JSON терминальные окна вектором. Приглашения и наборы
ввода заданы явно: если приглашение не найдено или программа вернула
неожидаемый код возврата, генерация падает, чтобы рисунки не врали.
"""
import json
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent  # home/
ASSETS = ROOT / "report" / "assets"
TITLE = "sehaxe@cachyos: ~/OAiP-Laba6/home"

SIZE = "Размер массива n (1..100): "
MODE = "Заполнение: 1 - вручную, 2 - случайно: "
N = "Строк n (1..20): "
M = "Столбцов m (1..20): "


def array_prompts(n: int) -> list[str]:
    return [SIZE, MODE] + [f"a[{i}] = " for i in range(n)]


def matrix_prompts(n: int, m: int) -> list[str]:
    return [N, M, MODE] + [f"a[{i}][{j}] = " for i in range(n) for j in range(m)]


SESSIONS = {
    1: [
        (array_prompts(7), ["7", "1", "5", "12", "8", "-6", "2", "9", "4"]),
        (array_prompts(4), ["4", "1", "4", "9", "3", "5"]),
    ],
    2: [
        (matrix_prompts(3, 3), ["3", "3", "1", "1", "-2", "3", "4", "5",
                                 "-6", "-7", "2", "-8"]),
        (matrix_prompts(2, 3), ["2", "3", "1", "5", "-5", "0",
                                 "-2", "-3", "-4"]),
    ],
}

EXPECTED = {
    (1, 0): "-6    2    4    9    8",
    (1, 1): "4    9    3    5",
    (2, 0): "   -7    2   -8",
    (2, 1): "   -2   -3   -4",
}


def screen_lines(prompts: list[str], user_input: str, out: str) -> list[dict]:
    inputs = user_input.split("\n") if user_input else []
    if len(inputs) != len(prompts):
        raise RuntimeError(f"вводов {len(inputs)}, приглашений {len(prompts)}")
    lines: list[dict] = []
    pos = 0
    for prompt, answer in zip(prompts, inputs):
        idx = out.find(prompt, pos)
        if idx < 0:
            raise RuntimeError(f"приглашение не найдено: {prompt!r}")
        for text in out[pos:idx].splitlines():
            if text:
                lines.append({"out": text})
        lines.append({"echo": {"prompt": prompt, "input": answer}})
        pos = idx + len(prompt)
    for text in out[pos:].splitlines():
        if text:
            lines.append({"out": text})
    return lines


def run_task(n: int, runs: list[tuple[list[str], list[str]]]) -> list[dict]:
    session = []
    for k, (run_prompts, inputs) in enumerate(runs):
        user_input = "\n".join(inputs)
        proc = subprocess.run(
            [f"./{n}/main"],
            input=user_input + "\n",
            capture_output=True,
            text=True,
            cwd=ROOT,
        )
        if proc.returncode != 0:
            raise RuntimeError(f"task {n}: код возврата {proc.returncode}")
        want = EXPECTED[(n, k)]
        if want not in proc.stdout:
            raise RuntimeError(f"task {n}, запуск {k}: нет {want!r}")
        session.append({
            "cmd": f"./{n}/main",
            "lines": screen_lines(run_prompts, user_input, proc.stdout),
        })
    return session


if __name__ == "__main__":
    ASSETS.mkdir(parents=True, exist_ok=True)
    data = {}
    for n, runs in SESSIONS.items():
        data[str(n)] = {
            "title": TITLE,
            "dir": "~/OAiP-Laba6/home",
            "runs": run_task(n, runs),
        }
        print(f"ok: задача {n} ({len(runs)} запуска)")
    out = ASSETS / "term.json"
    out.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"ok: {out.relative_to(ROOT)}")
