<script context="module">
  import Markdown from "$lib/markdown.svelte";
  import { base } from "$app/paths";

  export async function load({ page, fetch, session, context }) {
    const res = await fetch("/posts/" + page.params.slug + ".json", {
      method: "GET",
      mode: "cors",
      headers: {
        "content-type": "application/json",
      },
    });

    const json = await res.json();

    if (res.ok) return { props: { markdown: json.meta } };

    return {
      status: res.status,
      error: new Error(`Could not load page.`),
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

  .info a {
    color: rgb(255, 62, 0);
    text-decoration: none;
  }
</style>
