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
</script>

{#each posts as post}
  <div class="post">
    <a href="posts/{post.url}">{post.meta.attributes.title}</a>

    <div>
      <p>By</p>
      <p id="author">{post.meta.attributes.author}</p>
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

  .post a {
    font-size: xx-large;
    color: white;
  }

  .post a:hover {
    text-decoration: underline;
  }

  #author {
    color: var(--color);
  }
</style>
