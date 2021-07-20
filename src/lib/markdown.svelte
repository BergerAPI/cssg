<!-- src/Markdown.svelte -->
<script>
  import MarkdownIt from "markdown-it";
  import hljs from "highlight.js";
  import "highlight.js/styles/atom-one-dark.css";

  export let markdown;

  var md = new MarkdownIt({
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

      return (
        '<pre class="hljs"><code>' + md.utils.escapeHtml(str) + "</code></pre>"
      );
    },
  });

  // Render to an html string
  const rendered = md.render(markdown);
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
