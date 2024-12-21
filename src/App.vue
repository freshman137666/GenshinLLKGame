<script setup lang="ts">
import { invoke } from '@tauri-apps/api/core';
import { listen } from '@tauri-apps/api/event';
import axios from "axios";



async function Sidecar() {
  try {
    await invoke('call_my_sidecar');
    console.log('Sidecar launched successfully');
  } catch (err) {
    console.error('Failed to launch Sidecar:', err);
  }
}
Sidecar();

const exitProgram = async () => {
  try {
    await axios.post("http://localhost:11451/bye");
    console.log("Goodbye request sent!");
  } catch (error) {
    console.error("Error sending goodbye request:", error);
  }
};

// 监听 exit-program 事件
listen('exit-program', () => {
  exitProgram();
});

</script>

<template>
 <main>
 <router-view/>
 </main>
</template>

<style scoped>
</style>