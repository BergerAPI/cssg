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
  import { goto } from "$app/navigation";

  export let posts;

  function onClick(post) {
    goto("/posts/" + post.url);
  }
</script>

<div class="posts">
  {#each posts as post}
    <div class="post" on:click={onClick(post)}>
      <h1>{post.meta.attributes.title}</h1>
      <p>By</p>
      <a href={"https://github.com/" + post.meta.attributes.author}
        >{post.meta.attributes.author}</a
      >
    </div>
  {/each}
</div>

<style>
  .post {
    margin-bottom: var(--margin);
  }
  .post a,
  p {
    display: inline;
  }
</style>
