<script>
  import fs from "fs";
  let posts = fs.readdirSync("static/posts");
</script>

{#each posts as post}
  <a href={"posts/" + post.split(".")[0]}>{post.split(".")[0]}</a>
{/each}
