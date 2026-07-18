/* =========================================================
   강의 페이지 생성기 (Node)
   - 각 session_NN/ 의 lecture.md(혼합 노트) + practice.md(실습)를
     하나의 self-contained lesson.html 로 합치고,
   - 폴더의 정답 코드(.c / Makefile / libsbs.h)를 토글 카드로 삽입.
   실행: node build_lessons.js
   ========================================================= */

const fs = require("fs");
const path = require("path");

const ROOT = __dirname;

const TITLES = {
  1: "환경 세팅 + C언어 첫걸음", 2: "변수, 자료형, 연산자", 3: "조건문과 반복문",
  4: "함수와 재귀", 5: "포인터 기초", 6: "배열과 포인터", 7: "문자열과 포인터",
  8: "구조체와 typedef", 9: "헤더 파일 + 문자 분류 함수", 10: "메모리 함수 I",
  11: "동적 메모리와 malloc", 12: "문자열 함수 I", 13: "문자열 함수 II",
  14: "문자열 비교와 변환", 15: "Makefile과 라이브러리", 16: "종합 프로젝트 + 코드 리뷰"
};

/* ---------- 최소 마크다운 → HTML ---------- */
function esc(s) {
  return s.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
}
// 코드 보호용 sentinel (본문에 등장하지 않는 private-use 문자)
const OPEN = "";
const CLOSE = "";
function inline(s) {
  const codes = [];
  s = s.replace(/`([^`]+)`/g, (m, c) => {
    codes.push("<code>" + esc(c) + "</code>");
    return OPEN + (codes.length - 1) + CLOSE;
  });
  s = esc(s);
  s = s.replace(/\*\*([^*]+)\*\*/g, "<strong>$1</strong>");
  s = s.replace(/\[([^\]]+)\]\(([^)]+)\)/g, '<a href="$2">$1</a>');
  s = s.replace(new RegExp(OPEN + "(\\d+)" + CLOSE, "g"), (m, i) => codes[+i]);
  return s;
}
// 코드 펜스 언어 → highlight.js 클래스 (ASCII 다이어그램 등은 하이라이트 제외)
function codeClass(lang) {
  lang = (lang || "").toLowerCase();
  if (lang === "c" || lang === "h") return "language-c";
  if (lang === "bash" || lang === "sh" || lang === "shell") return "language-bash";
  if (lang === "make" || lang === "makefile") return "language-makefile";
  return "nohighlight";
}
function mdToHtml(md) {
  const lines = md.replace(/\r\n/g, "\n").split("\n");
  let html = "";
  let i = 0;
  while (i < lines.length) {
    let line = lines[i];

    // 힌트 토글 (::: hint 제목 ... :::) — 학생이 원할 때만 펼쳐 보는 접이식 블록
    const hintOpen = line.match(/^:::\s*hint(?:\s+(.+))?\s*$/);
    if (hintOpen) {
      i++;
      let buf = [];
      while (i < lines.length && !/^:::\s*$/.test(lines[i])) { buf.push(lines[i]); i++; }
      i++;
      const label = hintOpen[1] || "힌트 보기";
      html += '<details class="hint"><summary>💡 ' + inline(label) + "</summary><div class=\"hint-body\">\n" +
        mdToHtml(buf.join("\n")) + "</div></details>\n";
      continue;
    }

    // 코드 펜스
    const fence = line.match(/^```(\w*)/);
    if (fence) {
      i++;
      let buf = [];
      while (i < lines.length && !/^```/.test(lines[i])) { buf.push(lines[i]); i++; }
      i++;
      html += "<pre><code class=\"" + codeClass(fence[1]) + "\">" + esc(buf.join("\n")) + "</code></pre>\n";
      continue;
    }

    // 표
    if (/^\s*\|.*\|\s*$/.test(line) && i + 1 < lines.length && /^\s*\|[\s:|-]+\|\s*$/.test(lines[i + 1])) {
      const headCells = line.split("|").slice(1, -1).map(c => c.trim());
      i += 2;
      let rows = [];
      while (i < lines.length && /^\s*\|.*\|\s*$/.test(lines[i])) {
        rows.push(lines[i].split("|").slice(1, -1).map(c => c.trim()));
        i++;
      }
      html += "<table><thead><tr>" + headCells.map(c => "<th>" + inline(c) + "</th>").join("") + "</tr></thead><tbody>";
      rows.forEach(r => { html += "<tr>" + r.map(c => "<td>" + inline(c) + "</td>").join("") + "</tr>"; });
      html += "</tbody></table>\n";
      continue;
    }

    // 제목
    let h = line.match(/^(#{1,6})\s+(.*)$/);
    if (h) { html += "<h" + h[1].length + ">" + inline(h[2]) + "</h" + h[1].length + ">\n"; i++; continue; }

    // hr
    if (/^\s*---+\s*$/.test(line)) { html += "<hr />\n"; i++; continue; }

    // 인용
    if (/^\s*>\s?/.test(line)) {
      let buf = [];
      while (i < lines.length && /^\s*>\s?/.test(lines[i])) { buf.push(lines[i].replace(/^\s*>\s?/, "")); i++; }
      html += "<blockquote>" + buf.map(inline).join("<br />") + "</blockquote>\n";
      continue;
    }

    // 순서 없는 목록
    if (/^\s*[-*]\s+/.test(line)) {
      let buf = [];
      while (i < lines.length && /^\s*[-*]\s+/.test(lines[i])) { buf.push(lines[i].replace(/^\s*[-*]\s+/, "")); i++; }
      html += "<ul>" + buf.map(b => "<li>" + inline(b) + "</li>").join("") + "</ul>\n";
      continue;
    }

    // 순서 목록
    if (/^\s*\d+\.\s+/.test(line)) {
      let buf = [];
      while (i < lines.length && /^\s*\d+\.\s+/.test(lines[i])) { buf.push(lines[i].replace(/^\s*\d+\.\s+/, "")); i++; }
      html += "<ol>" + buf.map(b => "<li>" + inline(b) + "</li>").join("") + "</ol>\n";
      continue;
    }

    // 빈 줄
    if (/^\s*$/.test(line)) { i++; continue; }

    // 문단
    let buf = [line];
    i++;
    while (i < lines.length && !/^\s*$/.test(lines[i]) &&
           !/^(#{1,6}\s|```|\s*[-*]\s|\s*\d+\.\s|\s*>|\s*---+\s*$|\s*\|)/.test(lines[i])) {
      buf.push(lines[i]); i++;
    }
    html += "<p>" + buf.map(inline).join("<br />") + "</p>\n";
  }
  return html;
}

/* ---------- 정답 코드 토글 ---------- */
function answerCards(dir) {
  // dir(최상위)과, 있으면 dir/src(라이브러리 소스)를 함께 스캔
  function collect(base, prefix) {
    if (!fs.existsSync(base)) return [];
    return fs.readdirSync(base).filter(f => {
      const full = path.join(base, f);
      if (!fs.statSync(full).isFile()) return false;
      return /\.c$/.test(f) || f === "Makefile" || f === "libsbs.h";
    }).map(f => ({ name: prefix + f, full: path.join(base, f), base: f }));
  }
  let files = collect(dir, "");
  files = files.concat(collect(path.join(dir, "src"), "src/"));
  files.sort((a, b) => {
    const rank = x => x.base === "libsbs.h" ? 0 : x.base === "Makefile" ? 1 : 2;
    if (rank(a) !== rank(b)) return rank(a) - rank(b);
    return a.name.localeCompare(b.name);
  });
  if (files.length === 0) return "";
  let out = '<div class="section-split"><h2>정답 코드</h2><p>각 항목의 "정답 보기"를 눌러 펼치세요. 먼저 직접 풀어본 뒤 확인하는 것을 권장합니다.</p></div>\n';
  files.forEach(f => {
    const code = fs.readFileSync(f.full, "utf8").replace(/\s+$/, "");
    const cls = f.base === "Makefile" ? "language-makefile" : "language-c";
    out +=
      '<div class="answer">' +
        '<div class="answer-head">' +
          '<span class="answer-name">📄 <span class="file">' + f.name + "</span></span>" +
          '<button class="answer-toggle">정답 보기</button>' +
        "</div>" +
        '<div class="answer-body"><pre><code class="' + cls + '">' + esc(code) + "</code></pre></div>" +
      "</div>\n";
  });
  return out;
}

/* ---------- 페이지 템플릿 ---------- */
function page(n, bodyHtml, quizFile, starterZip) {
  const title = TITLES[n];
  const quizCta = quizFile
    ? `      <div class="quiz-cta">
        <span class="quiz-cta-label">📝 수업 마무리 퀴즈 (15문항)</span>
        <a class="quiz-btn" href="${quizFile}" target="_blank" rel="noopener">퀴즈 풀기</a>
        <a class="quiz-btn ghost" href="${quizFile}" download>내려받기</a>
      </div>\n`
    : "";
  const starterCta = starterZip
    ? `      <div class="quiz-cta starter">
        <span class="quiz-cta-label">📦 실습 파일 (Makefile 제외 전체)</span>
        <a class="quiz-btn amber" href="${starterZip}" download>실습 파일 내려받기</a>
      </div>\n`
    : "";
  return `<!doctype html>
<html lang="ko">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>${n}차시 · ${title} — C언어 입문 강의</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/gh/highlightjs/cdn-release@11.9.0/build/styles/atom-one-dark.min.css" />
    <link rel="stylesheet" href="../lesson.css" />
  </head>
  <body>
    <div id="readbar" class="readbar"></div>
    <nav class="topnav">
      <a class="back" href="../index.html">← 강의 목록</a>
      <span class="crumb">C언어 입문 강의 · ${n} / 16</span>
    </nav>
    <header class="lesson-hero">
      <div class="lesson-hero-inner">
        <span class="badge">${n <= 8 ? "C 기초" : "libsbs 구현"} · ${n}차시</span>
        <h1>${title}</h1>
${starterCta}${quizCta}      </div>
    </header>
    <main class="wrap">
      <article class="md">
${bodyHtml}
      </article>
    </main>
    <button id="toTop" class="to-top" aria-label="맨 위로">↑</button>
    <script>
      document.querySelectorAll(".answer-head").forEach(function (h) {
        h.addEventListener("click", function () {
          var card = h.parentElement;
          card.classList.toggle("open");
          h.querySelector(".answer-toggle").textContent =
            card.classList.contains("open") ? "정답 숨기기" : "정답 보기";
        });
      });
      var bar = document.getElementById("readbar");
      var toTopBtn = document.getElementById("toTop");
      function onScroll() {
        var y = window.scrollY || document.documentElement.scrollTop;
        var dh = document.documentElement.scrollHeight - window.innerHeight;
        var r = dh > 0 ? y / dh : 0;
        bar.style.width = (Math.min(1, Math.max(0, r)) * 100) + "%";
        toTopBtn.classList.toggle("show", y > 400);
      }
      window.addEventListener("scroll", onScroll, { passive: true });
      toTopBtn.addEventListener("click", function () { window.scrollTo({ top: 0, behavior: "smooth" }); });
      onScroll();
    </script>
    <script src="https://cdn.jsdelivr.net/gh/highlightjs/cdn-release@11.9.0/build/highlight.min.js"></script>
    <script>
      if (window.hljs) {
        document.querySelectorAll("pre code:not(.nohighlight)").forEach(function (el) { hljs.highlightElement(el); });
      }
    </script>
  </body>
</html>
`;
}

/* ---------- 빌드 ---------- */
let built = 0;
for (let n = 1; n <= 16; n++) {
  const nn = n < 10 ? "0" + n : "" + n;
  const dir = path.join(ROOT, "session_" + nn);
  if (!fs.existsSync(dir)) { console.log("skip session_" + nn); continue; }

  let body = "";
  const lecturePath = path.join(dir, "lecture.md");
  if (fs.existsSync(lecturePath)) {
    let lec = fs.readFileSync(lecturePath, "utf8").replace(/^#\s+.*\n/, "");
    body += mdToHtml(lec);
  }
  const practicePath = path.join(dir, "practice.md");
  if (fs.existsSync(practicePath)) {
    let prac = fs.readFileSync(practicePath, "utf8").replace(/^#\s+.*\n/, "");
    body += '<div class="section-split"><h2>실습</h2><p>아래 문제를 직접 풀어본 뒤, 맨 아래 정답 코드로 확인하세요.</p></div>\n';
    body += mdToHtml(prac);
  }
  body += answerCards(dir);

  const quizName = "quiz_" + nn + ".html";
  const quizFile = fs.existsSync(path.join(dir, quizName)) ? quizName : null;
  const starterName = "session_" + nn + "_starter.zip";
  const starterZip = fs.existsSync(path.join(dir, starterName)) ? starterName : null;

  fs.writeFileSync(path.join(dir, "lesson.html"), page(n, body, quizFile, starterZip), "utf8");
  built++;
  console.log("built session_" + nn + "/lesson.html");
}
console.log("\n총 " + built + "개 lesson.html 생성 완료");
