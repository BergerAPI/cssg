<script>
  export let navConfig;
</script>

<div class="full">
  <div class="flex content">
    <h2 id="logo">Portfolio</h2>

    <div class="routes flex">
      {#each navConfig as route}
        <a href={route.url}>{route.name}</a>
      {/each}
    </div>
  </div>
</div>

<style>
  .full {
    border-bottom: 1px solid black;
  }
  .content {
    max-width: 1000px;
    height: 50px;
    margin: 0 auto;
    justify-content: space-between;
  }
  #logo {
    margin-right: 10px;
  }
  .flex {
    display: flex;
    align-items: center;
  }

  .routes a {
    color: white;
    font-size: 1em;
    text-decoration: none;
    margin-left: 20px;
  }
</style>
