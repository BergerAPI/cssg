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
  import { base } from "$app/paths";

  export let posts;

  function onClick(post) {
    goto(base + "/posts/" + post.url);
  }
</script>

{#each posts as post}
  <div class="post" on:click={onClick(post)}>
    <h1>{post.meta.attributes.title}</h1>

    <p>By</p>
    <p id="author">{post.meta.attributes.author}</p>
  </div>
{/each}

<style>
  .post {
    margin-bottom: var(--margin);
    cursor: pointer;
    border-radius: 5px;
  }
  .post p {
    display: inline;
  }

  #author {
    color: var(--color);
  }
</style>
