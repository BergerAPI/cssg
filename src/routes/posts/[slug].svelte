<script context="module">
  import Markdown from "$lib/markdown.svelte";
  import { base } from "$app/paths";

  function isJson(str) {
    try {
      JSON.parse(str);
    } catch (e) {
      return false;
    }
    return true;
  }

  export async function load({ page, fetch, session, context }) {
    const res = await fetch(base + "/posts/" + page.params.slug + "-z.json", {
      method: "GET",
      mode: "cors",
      headers: {
        "content-type": "application/json",
      },
    });

    const text = await res.text();

    if (res.ok && isJson(text))
      return { props: { markdown: JSON.parse(text).meta } };

    return {
      status: res.status,
      error: new Error(`Could not load page. - ` + text),
    };
  }
</script>

<script>
  export let markdown;
</script>

<h1>{markdown.attributes.title}</h1>

<div class="info">
  <p>By</p>
  <a href={"https://github.com/" + markdown.attributes.author}
    >{markdown.attributes.author}</a
  >
  <p>on {markdown.attributes.date}</p>
</div>

<Markdown markdown={markdown.body} />

<style>
  .info p,
  a {
    display: inline;
  }
</style>
