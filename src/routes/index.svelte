<script>
  import Markdown from "$lib/markdown.svelte";
  import fs from "fs";

  let markdown = fs.readFileSync("static/index.md", "utf8");
</script>

<Markdown {markdown} />
