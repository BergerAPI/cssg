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
    renderMathInElement(document.body, {
      // customised options
      // • auto-render specific keys, e.g.:
      delimiters: [
        { left: "$$", right: "$$", display: true },
        { left: "$", right: "$", display: false },
        { left: "\\(", right: "\\)", display: false },
        { left: "\\[", right: "\\]", display: true },
      ],
      // • rendering keys, e.g.:
      throwOnError: false,
    });

    var classes = document.getElementsByClassName("katex");
    for (let i = 0; i < classes.length; i++) {
      let element = classes[i];

      element.classList.add("hljs");
    }
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
