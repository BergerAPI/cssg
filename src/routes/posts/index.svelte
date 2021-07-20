<script context="module">
  export async function load({ fetch }) {
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
  <a href={"posts/" + post.url}>{post.meta.attributes.title}</a>
{/each}
