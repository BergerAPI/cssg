<script>
  import Nav from "$lib/navbar.svelte";

  let navConfig = [
    {
      name: "Home",
      url: "/",
    },
    {
      name: "Posts",
      url: "/posts",
    },
  ];

  const routerObject = {};
  navConfig.forEach((route) => (routerObject[route.path] = route.object));
</script>

<Nav {navConfig} />
<div class="content">
  <slot />
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
      margin-top: var(--margin);
    }
  }
</style>
