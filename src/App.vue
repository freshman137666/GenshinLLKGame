<script setup lang="ts">
import { invoke } from '@tauri-apps/api/core';

async function Sidecar() {
  try {
    await invoke('call_my_sidecar');
    console.log('Sidecar launched successfully');
  } catch (err) {
    console.error('Failed to launch Sidecar:', err);
  }
}
Sidecar();
</script>

<template>
 <main>
 <router-view/>
 </main>
</template>

<style scoped>
</style>