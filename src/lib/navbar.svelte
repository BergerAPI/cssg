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

  <div class="socials">
    {#each socials as social}
      <a href={social.url}>
        <i class={"fab fa-lg " + social.icon} />
      </a>
    {/each}
  </div>
</div>

<style>
  .content {
    max-width: 75%;
    margin: 0 auto;
    height: 50px;
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

  @media (max-width: 450px) {
    .socials {
      visibility: hidden;
    }
  }
</style>
