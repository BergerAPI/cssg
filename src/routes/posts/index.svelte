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

<svelte:head>
  <title>Posts</title>
</svelte:head>

{#each posts as post}
  <div class="post">
    <a id="title" href="posts/{post.url}">{post.meta.attributes.title}</a>

    <div>
      <p>By</p>
      <a id="author" href="https://github.com/{post.meta.attributes.author}"
        >{post.meta.attributes.author}</a
      >
    </div>
  </div>
{/each}

<style>
  .post {
    margin-bottom: var(--margin);
    border-radius: 5px;
  }
  .post p {
    display: inline;
  }

  .post #title {
    font-size: xx-large;
    font-weight: bold;
    color: white;
  }

  .post a:hover {
    text-decoration: underline;
  }

  .post #author {
    color: var(--color);
  }
</style>
