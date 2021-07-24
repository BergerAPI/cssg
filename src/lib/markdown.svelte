<!-- src/Markdown.svelte -->
<script>
  import { Remarkable } from "remarkable";
  import hljs from "highlight.js";
  import "highlight.js/styles/atom-one-dark.css";
  import { onMount } from "svelte";

  export let markdown;

  let md = new Remarkable({
    highlight: (str, lang) => {
      if (lang && hljs.getLanguage(lang)) {
        try {
          return (
            '<pre class="hljs"><code>' +
            hljs.highlight(str, { language: lang, ignoreIllegals: true })
              .value +
            "</code></pre>"
          );
        } catch (__) {}
      }
      return "";
    },
    html: true,
  });

  // Render to an html string
  const rendered = md.render(markdown);

  onMount(() => {
    let script = document.createElement("script");
    script.src = "https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js";
    document.head.append(script);

    script.onload = () => {
      MathJax = {
        tex: {
          inlineMath: [
            ["$", "$"],
            ["\\(", "\\)"],
          ],
        },
        svg: { fontCache: "global" },
      };
    };
  });
</script>

<div class="rendered">
  {@html rendered}
</div>

<style type="text/css">
  .rendered {
    font-family: sans-serif;
  }

  .rendered {
    margin-top: var(--margin);
  }
</style>
