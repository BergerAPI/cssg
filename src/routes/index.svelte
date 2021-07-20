<script context="module">
  import Markdown from "$lib/markdown.svelte";

  export async function load({ page, fetch, session, context }) {
    const res = await fetch("/index.md", {
      method: "GET",
      mode: "cors",
      headers: {
        "content-type": "application/json",
      },
    });

    if (res.ok) return { props: { markdown: await res.text() } };

    return {
      status: res.status,
      error: new Error(`Could not load page.`),
    };
  }
</script>

<script>
  export let markdown;
</script>

<Markdown {markdown} />
