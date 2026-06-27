/* =========================================================
   libsbs 따라잡기 페이지 동작
   - 사이드바 네비 스크롤 스파이 + 진도 표시
   - 모바일 메뉴 토글
   - 코드 복사 버튼
   - 읽기 진행 바 + 맨 위로 버튼
   ========================================================= */

(function () {
  "use strict";

  var sidebar = document.getElementById("sidebar");
  var overlay = document.getElementById("overlay");
  var menuBtn = document.getElementById("menuBtn");
  var navLinks = Array.prototype.slice.call(document.querySelectorAll(".nav-link"));
  var sections = navLinks
    .map(function (a) { return document.querySelector(a.getAttribute("href")); })
    .filter(Boolean);
  var readbar = document.getElementById("readbar");
  var toTop = document.getElementById("toTop");
  var progressPct = document.getElementById("progressPct");

  /* ---------- 모바일 메뉴 ---------- */
  function openMenu() { sidebar.classList.add("open"); overlay.classList.add("show"); }
  function closeMenu() { sidebar.classList.remove("open"); overlay.classList.remove("show"); }

  if (menuBtn) menuBtn.addEventListener("click", openMenu);
  if (overlay) overlay.addEventListener("click", closeMenu);
  navLinks.forEach(function (a) {
    a.addEventListener("click", function () {
      if (window.innerWidth <= 860) closeMenu();
    });
  });

  /* ---------- 코드 복사 ---------- */
  document.querySelectorAll(".code .copy").forEach(function (btn) {
    btn.addEventListener("click", function () {
      var codeEl = btn.parentElement.querySelector("code");
      if (!codeEl) return;
      var text = codeEl.innerText;

      var done = function () {
        var orig = "복사";
        btn.textContent = "복사됨!";
        btn.classList.add("done");
        setTimeout(function () {
          btn.textContent = orig;
          btn.classList.remove("done");
        }, 1400);
      };

      if (navigator.clipboard && navigator.clipboard.writeText) {
        navigator.clipboard.writeText(text).then(done, function () { fallback(text, done); });
      } else {
        fallback(text, done);
      }
    });
  });

  function fallback(text, done) {
    var ta = document.createElement("textarea");
    ta.value = text;
    ta.style.position = "fixed";
    ta.style.opacity = "0";
    document.body.appendChild(ta);
    ta.select();
    try { document.execCommand("copy"); done(); } catch (e) { /* noop */ }
    document.body.removeChild(ta);
  }

  /* ---------- 스크롤 스파이 + 진행 바 ---------- */
  function onScroll() {
    var y = window.scrollY || document.documentElement.scrollTop;

    /* 읽기 진행 바 */
    var docH = document.documentElement.scrollHeight - window.innerHeight;
    var ratio = docH > 0 ? (y / docH) : 0;
    if (ratio < 0) ratio = 0;
    if (ratio > 1) ratio = 1;
    readbar.style.width = (ratio * 100) + "%";
    if (progressPct) progressPct.textContent = Math.round(ratio * 100) + "%";

    /* 맨 위로 버튼 */
    if (y > 400) toTop.classList.add("show");
    else toTop.classList.remove("show");

    /* 활성 섹션 찾기 */
    var current = sections[0];
    var offset = 120;
    for (var i = 0; i < sections.length; i++) {
      if (sections[i].getBoundingClientRect().top - offset <= 0) {
        current = sections[i];
      }
    }
    if (current) {
      var id = current.getAttribute("id");
      navLinks.forEach(function (a) {
        a.classList.toggle("active", a.getAttribute("href") === "#" + id);
      });
    }
  }

  window.addEventListener("scroll", onScroll, { passive: true });
  window.addEventListener("resize", onScroll);
  onScroll();

  /* ---------- 맨 위로 ---------- */
  toTop.addEventListener("click", function () {
    window.scrollTo({ top: 0, behavior: "smooth" });
  });
})();
