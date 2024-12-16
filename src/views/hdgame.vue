<script setup lang="ts">
import anime from 'animejs';
import { onMounted, ref, watch } from 'vue';
import bgmusic_ from '../music/ez1.flac'
import rightmusic_ from '../music/right.mp3'
import wrongmusic_ from '../music/wrong.mp3'
import endmusic_ from '../assets/music/endgame.wav'
import hdbg from '../icons/hardbg.mp4'
import tourist from '../assets/icons/avatar.png'
import axios from 'axios';
import { useStore } from '../store/counter';
import { useRouter } from 'vue-router';


const router =useRouter();
const store =useStore();
const sltbut = ref();
const bfbut = ref();
const select1 = ref(null);
const bgmusic = ref(new Audio(bgmusic_))
const rightmusic = ref(new Audio(rightmusic_))
const wrongmusic =ref(new Audio(wrongmusic_))
const endmusic =ref(new Audio(endmusic_))
const hpnums = ref(100);
const allnums = ref(40);
const result = ref(0);
const comble =ref(0);
let intervalId:number |null =null;
const isTrue =ref("");
const selectmessage =ref("");


const centerDialogVisible = ref(false)
const endgame =()=>{
    endmusic.value.play();
    store.gate.score=result.value;
    store.addData();
    bgmusic.value.pause();
    centerDialogVisible.value = true
}
const returnSelect=()=>{
    centerDialogVisible.value =false;
    router.push('/select');
}

const drs =()=>{
    if(hpnums.value>0){
        hpnums.value--;
    }
}

const nocomble=()=>{
    comble.value=0;
    anime({
        targets:'.combo',
        opacity:0
    }).finished
}
const isselected =(e:MouseEvent)=>{
    const btn = e.target as HTMLButtonElement;
    sltbut.value=btn;
    console.log(btn.value);  
}
const matchsuccess=(e1:HTMLButtonElement,e2:HTMLButtonElement)=>{
    hpnums.value+=20;
    anime({
        targets:[e1,e2],
        scale:0
    }).finished
    rightmusic.value.play();
    comble.value++;
    clearInterval(intervalId!);
    intervalId=setInterval(nocomble,2000);
    result.value+=10;
    allnums.value--;
    switch(comble.value){
        case 1:break;
        case 2:result.value+=10;anime({
            targets:'.combo',
            opacity:1
        });break;
        case 3:result.value+=30;anime({
            targets:'.combo',
            opacity:1
        }); break;
        case 4:result.value+=60;anime({
            targets:'.combo',
            opacity:1
        }); break;
        case 5:result.value+=100;anime({
            targets:'.combo',
            opacity:1
        }); break;
        default:result.value+=100;anime({
            targets:'.combo',
            opacity:1
        }); break;
    }
}

const matchfaild=(e1:HTMLButtonElement,e2:HTMLButtonElement)=>{
    wrongmusic.value.play();
    anime({
        targets:[e1,e2],
        scale:1
    }).finished
}

const istrue =async()=>{
    try {
        const response = await axios.post("http://localhost:11451/selected",selectmessage.value);
        isTrue.value=JSON.parse(response.data);
    } catch (error) {
        console.error("Error fetching state:", error);
    }
}

const matchpos=async (e1:HTMLButtonElement,e2:HTMLButtonElement)=>{
    console.log(e1.value +","+ e2.value);
    selectmessage.value=`${e1.value},${e2.value}`;
    await istrue();
    if(isTrue.value){
        matchsuccess(e1,e2);
    }
    else{
        matchfaild(e1,e2);
    }
}

const onMouse=()=>{
    if(sltbut.value==null)return;
    if(bfbut.value!=sltbut.value)
{
    anime({
    targets:sltbut.value,
    scale:1.5
          }).finished
    bfbut.value=sltbut.value;
    if(select1.value==null){
    select1.value=sltbut.value;
    }
else{
    const s1 =select1.value as HTMLButtonElement;
    const s2 =sltbut.value as HTMLButtonElement;
    matchpos(s1,s2);
    select1.value=null;
    sltbut.value=null;
    bfbut.value=null;
    }
}
    else{
        anime({
            targets:sltbut.value,
            scale:1
        }).finished
        bfbut.value=null;
        select1.value=null;
    }
}

onMounted(()=>{
    anime({
        targets:'.rows',
        
        scale: [
    {value: .1, easing: 'easeOutSine', duration: 500},
    {value: 1, easing: 'easeInOutQuad', duration: 1200}
  ],
  delay: anime.stagger(200, {grid: [14, 5], from: 'center'})
    }).finished

    bgmusic.value.volume=0.3;
    setTimeout(() => {
        bgmusic.value.play();
  }, 3000);

  setInterval(drs,1000);
  intervalId = setInterval(nocomble,2000);
})

watch(allnums,(value)=>{
    if(value<=0){
        result.value+=hpnums.value*10;
        endgame();
    }
})

watch(hpnums,(value)=>{
    if(value<=0){
        endgame();
    }
})
const colors = [
  { color: '#f56c6c', percentage: 20 },
  { color: '#e6a23c', percentage: 40 },
  { color: '#5cb87a', percentage: 60 },
  { color: '#1989fa', percentage: 80 },
  { color: '#6f7ad3', percentage: 100 },
]
</script>

<template>
    <el-dialog v-model="centerDialogVisible" title="任务成功！！" width="500" center>
    <span>
      你的得分：{{ result }}
    </span>
    <template #footer>
      <div class="dialog-footer">
        <el-button type="primary" @click="returnSelect">
          返回主菜单
        </el-button>
      </div>
    </template>
  </el-dialog>
<div class="container">
    <video :src="hdbg"  autoplay loop playsinline class="bg"></video>
    <div class="play" @click="onMouse">
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bA" value="1-1" @click="isselected"></button>
        </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bB" value="1-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bC" value="1-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bD" value="1-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bE" value="1-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bF" value="1-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bG" value="1-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bH" value="1-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bI" value="1-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bJ" value="1-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bK" value="1-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bL" value="1-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bE" value="1-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bM" value="1-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bN" value="2-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bM" value="2-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bH" value="2-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bO" value="2-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bK" value="2-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bP" value="2-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bQ" value="2-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bG" value="2-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bC" value="2-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bH" value="2-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bM" value="2-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bR" value="2-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bR" value="2-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bL" value="2-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bR" value="3-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bS" value="3-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bT" value="3-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bK" value="3-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bU" value="3-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bV" value="3-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bP" value="3-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bW" value="3-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bO" value="3-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bX" value="3-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bO" value="3-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bD" value="3-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bV" value="3-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bY" value="3-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bQ" value="4-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bD" value="4-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bJ" value="4-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bG" value="4-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bP" value="4-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bP" value="4-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bR" value="4-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bX" value="4-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bC" value="4-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bZ" value="4-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bX" value="4-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bT" value="4-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAA" value="4-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bH" value="4-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bW" value="5-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bY" value="5-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bI" value="5-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAC" value="5-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAB" value="5-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bL" value="5-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bQ" value="5-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bT" value="5-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bB" value="5-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bU" value="5-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bN" value="5-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bM" value="5-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAB" value="5-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bW" value="5-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bF" value="6-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAD" value="6-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bX" value="6-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAA" value="6-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bA" value="6-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bY" value="6-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bZ" value="6-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bA" value="6-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bS" value="6-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAA" value="6-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bF" value="6-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAC" value="6-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bJ" value="6-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bA" value="6-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bD" value="7-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bG" value="7-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAC" value="7-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bZ" value="7-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bW" value="7-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bR" value="7-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bN" value="7-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAB" value="7-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bJ" value="7-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAD" value="7-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bI" value="7-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bZ" value="7-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bK" value="7-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAD" value="7-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bR" value="8-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAD" value="8-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bB" value="8-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAB" value="8-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bC" value="8-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAA" value="8-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bP" value="8-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bM" value="8-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bL" value="8-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bY" value="8-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bJ" value="8-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bR" value="8-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bP" value="8-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bT" value="8-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bS" value="9-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bU" value="9-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bY" value="9-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bX" value="9-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bB" value="9-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bX" value="9-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAB" value="9-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bE" value="9-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bQ" value="9-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bQ" value="9-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bN" value="9-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bQ" value="9-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bJ" value="9-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bF" value="9-14" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="1.71" class="cols">
                <button class="bY" value="10-1" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bM" value="10-2" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAC" value="10-3" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bI" value="10-4" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bE" value="10-5" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bV" value="10-6" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bU" value="10-7" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bS" value="10-8" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bR" value="10-9" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bU" value="10-10" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bU" value="10-11" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bAB" value="10-12" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bV" value="10-13" @click="isselected"></button>
            </el-col>
            <el-col :span="1.71" class="cols">
                <button class="bO" value="10-14" @click="isselected"></button>
            </el-col>
        </el-row>
    </div>
    <el-avatar class="avatar" :size="100" :src="tourist" />
    <div class="hp">
        <el-progress type="dashboard" :percentage="hpnums" :color="colors" :width="140"/>
    </div>
    <el-text class="score">得分:{{ result }}</el-text>
    <el-text class="combo">COMBO! {{ comble }}</el-text>
</div>
</template>

<style scoped>
.score{
    font-size: 7vw;
    color: rgb(63, 155, 236);
    margin-left: 20px;
    margin-top: 20px;
}
.combo{
    font-size: 3vw;
    position: absolute;
    top: 30px;
    left: 350px;
    color: #B15737;
    opacity: 1;
}
.hp{
    position: absolute;
    bottom: 24px;
    right: 25px;
}
.avatar{
    position: absolute;
    height: 130px;
    width: 130px;
    bottom: 30px;
    right: 30px;
}
.bg{
  position: absolute;
  width: 100%;
  height: 100%;
  z-index: -1;
  object-fit: cover;
  object-position: left;
}

.play{
    position: absolute;
    background: rgba(147, 191, 220,0.5);
    width: 48vw;
    height: 68vh;
    left: 3vw;
    top: 25vh;
}
.rows{
    height: 6vh;
    margin-top: 4px;
}
.cols{
    width: 6vh;
    height: 6vh; 
}
.bA{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/A.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bB{

    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/B.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bC{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/C.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bD{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/D.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bE{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/E.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bF{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/F.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bG{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/G.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bH{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/H.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bI{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/I.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bJ{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/J.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bK{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/K.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bL{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/L.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bM{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/M.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bN{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/N.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bO{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/O.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bP{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/P.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bQ{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/Q.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bR{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/R.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bS{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/S.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bT{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/T.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bU{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/U.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bV{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/V.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bW{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/W.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bX{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/X.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bY{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/Y.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bZ{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/Z.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bAA{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/AA.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bAB{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/AB.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bAC{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/AC.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
.bAD{
    height: 100%;
    width: 100%;
    background: url(../assets/icons/abc/AD.png);
    background-position: center;
    background-size: cover;
    border: none;
    opacity:1 ;
    isolation: isolate;
    border: 1px;
    border-style: solid;
    border-color: gold;
}
</style>