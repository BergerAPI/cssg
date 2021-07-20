<script context="module">
  import fs from "fs";

  export async function load({ page, fetch, session, context }) {
    const res = await fetch("/posts.json", {
      method: "GET",
      mode: "cors",
      headers: {
        "content-type": "application/json",
      },
    });

    const json = await res.json();

    if (res.ok) return { props: { posts: await json.posts } };

    return {
      status: res.status,
      error: new Error(`Could not load page.`),
    };
  }
</script>

<script>
  export let posts;
</script>

{#each posts as post}
  <a href={"posts/" + post}>{post}</a>
{/each}
