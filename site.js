/* =========================================================
   C언어 입문 강의 허브 — 동작 (정적, 진행 추적 없음)
   - 16차시 데이터 렌더 (카드 → 각 강의 페이지 lesson.html)
   - 검색 / 그룹 필터 / 맨 위로
   ========================================================= */

(function () {
  "use strict";

  var SESSIONS = [
    { n: 1, group: "basic", title: "환경 세팅 + C언어 첫걸음",
      goal: "GitHub Codespaces로 개발 환경을 켜고, gcc로 컴파일·실행하며 C 소스 구조와 printf를 익힌다.",
      tags: ["Codespaces", "gcc", "main", "printf"], folder: "session_01" },
    { n: 2, group: "basic", title: "변수, 자료형, 연산자",
      goal: "int·char·float·double 자료형과 sizeof, 형 변환, 산술·비교·논리 연산자를 사용한다.",
      tags: ["자료형", "sizeof", "형변환", "연산자"], folder: "session_02" },
    { n: 3, group: "basic", title: "조건문과 반복문",
      goal: "if/switch 조건 분기와 for/while/do-while 반복, break·continue 흐름 제어를 구현한다.",
      tags: ["if", "switch", "for/while", "break"], folder: "session_03" },
    { n: 4, group: "basic", title: "함수와 재귀",
      goal: "함수 선언·정의·호출, 값에 의한 전달, 스택 프레임, 재귀를 이해하고 구현한다.",
      tags: ["함수", "프로토타입", "값 전달", "재귀"], folder: "session_04" },
    { n: 5, group: "basic", title: "포인터 기초",
      goal: "주소와 역참조(&, *), 포인터 선언, 포인터로 원본 수정, swap을 구현한다.",
      tags: ["포인터", "주소", "역참조", "swap"], folder: "session_05" },
    { n: 6, group: "basic", title: "배열과 포인터",
      goal: "배열의 메모리 배치, 배열 이름=주소, 포인터 산술, 버블 정렬을 구현한다.",
      tags: ["배열", "포인터 산술", "정렬"], folder: "session_06" },
    { n: 7, group: "basic", title: "문자열과 포인터",
      goal: "char 배열 + null terminator 구조, 포인터 순회, 대소문자 변환·뒤집기를 구현한다.",
      tags: ["문자열", "\\0", "ASCII"], folder: "session_07" },
    { n: 8, group: "basic", title: "구조체와 typedef",
      goal: "구조체 선언, 멤버 접근(. / ->), typedef, 구조체 배열·포인터를 다룬다.",
      tags: ["struct", "typedef", "-> 접근"], folder: "session_08" },
    { n: 9, group: "impl", title: "헤더 파일 + 문자 분류 함수",
      goal: "헤더 파일·인클루드 가드를 이해하고 is*/toupper/tolower 7개를 직접 구현한다.",
      tags: ["헤더", "include 가드", "문자 분류"], folder: "session_09" },
    { n: 10, group: "impl", title: "메모리 함수 I",
      goal: "void*·바이트 단위 처리로 memset/bzero/memcpy/memccpy(+memchr/memcmp)를 구현한다.",
      tags: ["void*", "memset", "memcpy"], folder: "session_10" },
    { n: 11, group: "impl", title: "동적 메모리와 malloc",
      goal: "스택 vs 힙, malloc/free로 calloc·substr·strjoin·itoa로 새 문자열을 만든다.",
      tags: ["malloc", "free", "calloc", "strjoin"], folder: "session_11" },
    { n: 12, group: "impl", title: "문자열 함수 I",
      goal: "strlen, 버퍼 안전 strlcpy·strlcat을 구현하고 잘림 감지를 이해한다.",
      tags: ["strlen", "strlcpy", "버퍼 안전"], folder: "session_12" },
    { n: 13, group: "impl", title: "문자열 함수 II",
      goal: "순/역방향 검색 strchr·strrchr, 부분 문자열 strnstr을 구현한다.",
      tags: ["strchr", "strrchr", "strnstr"], folder: "session_13" },
    { n: 14, group: "impl", title: "문자열 함수 III",
      goal: "strncmp 비교, atoi 파싱(부호·공백), strdup 동적 복제를 구현한다.",
      tags: ["strncmp", "atoi", "strdup"], folder: "session_14" },
    { n: 15, group: "impl", title: "Makefile과 라이브러리",
      goal: "Makefile 문법과 ar로 libsbs.a 정적 라이브러리를 빌드하고 링크한다.",
      tags: ["Makefile", "ar", "libsbs.a"], folder: "session_15" },
    { n: 16, group: "impl", title: "종합 프로젝트 + 코드 리뷰",
      goal: "24개 함수를 libsbs로 통합하고, 통합 Makefile과 동료 코드 리뷰로 마무리한다.",
      tags: ["통합", "코드 리뷰", "libsbs"], folder: "session_16" }
  ];

  function pad(n) { return n < 10 ? "0" + n : "" + n; }
  function lessonPath(s) { return s.folder + "/lesson.html"; }

  var listEl = document.getElementById("lessonList");

  function render() {
    listEl.innerHTML = "";
    SESSIONS.forEach(function (s) {
      var li = document.createElement("li");
      li.className = "lesson";
      li.dataset.group = s.group;
      li.dataset.search = (s.n + "차시 " + s.title + " " + s.goal + " " + s.tags.join(" ")).toLowerCase();

      var badge = s.group === "basic"
        ? '<span class="lesson-badge badge-basic">C 기초</span>'
        : '<span class="lesson-badge badge-impl">libsbs 구현</span>';

      var tags = s.tags.map(function (t) { return '<span class="lb-tag">' + t + "</span>"; }).join("");

      li.innerHTML =
        '<a class="lesson-link" href="' + lessonPath(s) + '">' +
          '<div class="lesson-num">' + pad(s.n) + "</div>" +
          '<div class="lesson-main">' +
            '<div class="lesson-title">' + s.n + "차시 · " + s.title + badge + "</div>" +
            '<div class="lesson-desc">' + s.goal + "</div>" +
            '<div class="lb-tags">' + tags + "</div>" +
          "</div>" +
          '<span class="go">강의 보기 →</span>' +
        "</a>";

      listEl.appendChild(li);
    });
  }

  /* 검색 + 필터 */
  var currentGroup = "all";
  var searchInput = document.getElementById("search");
  var emptyMsg = document.getElementById("emptyMsg");

  function applyFilter() {
    var q = searchInput.value.trim().toLowerCase();
    var shown = 0;
    Array.prototype.forEach.call(listEl.children, function (li) {
      var okGroup = currentGroup === "all" || li.dataset.group === currentGroup;
      var okSearch = q === "" || li.dataset.search.indexOf(q) !== -1;
      var show = okGroup && okSearch;
      li.classList.toggle("hidden", !show);
      if (show) shown++;
    });
    emptyMsg.classList.toggle("hidden", shown !== 0);
  }

  searchInput.addEventListener("input", applyFilter);
  document.getElementById("filters").addEventListener("click", function (e) {
    var btn = e.target.closest(".filter");
    if (!btn) return;
    currentGroup = btn.dataset.group;
    Array.prototype.forEach.call(this.children, function (b) { b.classList.toggle("active", b === btn); });
    applyFilter();
  });

  /* 맨 위로 */
  var toTop = document.getElementById("toTop");
  window.addEventListener("scroll", function () {
    toTop.classList.toggle("show", window.scrollY > 400);
  }, { passive: true });
  toTop.addEventListener("click", function () { window.scrollTo({ top: 0, behavior: "smooth" }); });

  render();
  applyFilter();
})();
