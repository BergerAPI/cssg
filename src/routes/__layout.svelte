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

  let socials = [
    {
      url: "https://github.com/bergerapi",
      icon: "fa-github",
    },
    {
      url: "https://twitter.com/dreckigeruser",
      icon: "fa-twitter",
    },
  ];
</script>

<Nav {navConfig} {socials}>
  <a href="https://github.com/BergerAPI">
    <i class="fab fa-github fa-lg" />
  </a>
</Nav>

<div class="content">
  <slot />
</div>

<style lang="scss">
  .content {
    max-width: var(--responsive-v);
    margin: auto;
    margin-top: var(--margin);
  }

  @media (max-width: 840px) {
    .content {
      margin: var(--margin);
      max-width: none;
    }
  }
</style>
