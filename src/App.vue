<script setup lang="ts">
import { invoke } from '@tauri-apps/api/core';
import axios from "axios";
import { TauriEvent } from '@tauri-apps/api/event';
import { getCurrentWindow } from "@tauri-apps/api/window";
import { onMounted } from 'vue';


async function Sidecar() {
  try {
    await invoke('call_my_sidecar');
    console.log('Sidecar launched successfully');
  } catch (err) {
    console.error('Failed to launch Sidecar:', err);
  }
}
Sidecar();


const closeTauri=async()=>{
  try {
    await invoke('close_tauri');
    console.log('Sidecar launched successfully');
  } catch (err) {
    console.error('Failed to launch Sidecar:', err);
  }
}

onMounted(async()=>{
  getCurrentWindow().once(TauriEvent.WINDOW_CLOSE_REQUESTED,async () => {
  try {
     await axios.post("http://localhost:11451/bye");
   } catch (error) {
     console.error("Error while sending POST request:", error);
   } finally {
     closeTauri(); 
   }
})
}
)

</script>

<template>
 <main>
 <router-view/>
 </main>
</template>

<style scoped>
</style>