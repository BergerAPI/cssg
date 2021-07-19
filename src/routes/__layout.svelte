<script>
  import Nav from "$lib/navbar.svelte";
</script>

<div class="g-app-wrapper">
  <Nav />
  <div class="content">
    <slot />
  </div>
</div>

<style lang="scss">
  @media only screen and (max-width: 840px) {
    .content {
      margin: var(--margin);
    }
  }

  @media (min-width: 840px) {
    .content {
      max-width: var(--responsive-v);
      margin: auto;
    }
  }
</style>
