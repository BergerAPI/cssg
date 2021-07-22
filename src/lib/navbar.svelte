<script>
  export let navConfig = [];
  export let socials = [];
</script>

<div class="flex content">
  <div class="flex">
    <h2 id="logo">Portfolio</h2>

    <div class="routes flex">
      {#each navConfig as route}
        <a href={route.url}>{route.name}</a>
      {/each}
    </div>
  </div>

  <div>
    {#each socials as social}
      <a href={social.url}>
        <i class={"fab fa-lg " + social.icon} />
      </a>
    {/each}
  </div>
</div>

<style>
  .content {
    max-width: 1000px;
    height: 50px;
    margin: 0 auto;
    border-bottom: 1px solid rgb(27, 28, 28);
    justify-content: space-between;
  }

  .flex {
    display: flex;
    align-items: center;
  }

  .content a {
    color: white;
    font-size: 1em;
    text-decoration: none;
    margin-left: 20px;
  }
</style>
