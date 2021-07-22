<script>
  export let navConfig = [];
  export let socials = [];
</script>

<div class="flex content">
  <div class="flex">
    <h2 id="logo">BergerAPI</h2>

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

  .content #logo {
    border-right: 0.1em solid var(--color);
    overflow: hidden;
    animation: typing 3s steps(50, end), blink-caret 0.5s step-end infinite;
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

  @keyframes typing {
    from {
      width: 0;
    }
    to {
      width: 100%;
    }
  }
  @keyframes blink-caret {
    from,
    to {
      border-color: transparent;
    }
    50% {
      border-color: var(--color);
    }
  }
</style>
