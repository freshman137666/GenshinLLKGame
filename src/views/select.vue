<script setup lang="ts">
import { onMounted,  ref, watch } from "vue";
import anime from "animejs";
import { useRouter } from "vue-router";
import changemusic_ from '../music/bg_select.flac';
import selectmusic_ from '../music/select.wav';

const router =useRouter();
const animation = ref<anime.AnimeTimelineInstance>();
const startmove = ref(false);
const progress = ref(0);
const startY = ref(0);
const selected =ref(0);
const changemusic = ref(new Audio(changemusic_));
const selectmusic = ref(new Audio(selectmusic_))
const bgpic = ref('bg-4');


const onMouse=(e:MouseEvent)=>{
  e.preventDefault();
  startmove.value=true;
  startY.value=e.clientY;
}

const moveMouse=(e:MouseEvent)=>{
  if(!startmove.value)return;
  let dy =e.clientY-startY.value;
  progress.value+=dy/500;
  dy=0;
  startY.value=e.clientY;
  if(progress.value>=0.8)progress.value=0.8;
  if(progress.value<=0)progress.value=0;
  animation.value?.seek(progress.value*4*750);
}

const offMouse=()=>{
  startmove.value=false;
  if(progress.value>=0&&progress.value<0.05){
    animation.value?.seek(0);
    progress.value=0;
    selected.value=4;
  }
  if(progress.value>=0.05&&progress.value<0.30){
    animation.value?.seek(0.25*4*750);
    progress.value=0.25;
    selected.value=3;
  }
  if(progress.value>=0.30&&progress.value<0.55){
    animation.value?.seek(2*750);
    progress.value=0.5;
    selected.value=2;
  }
  if(progress.value>=0.55&&progress.value<=1){
    animation.value?.seek(0.8*4*750);
    progress.value=0.8;
    selected.value=1;
  }
}

const seek2=()=>{
  animation.value?.seek(2*750);
  progress.value=0.5;
  selected.value=2;
}

const seek4=()=>{
  animation.value?.seek(0);
  progress.value=0;
  selected.value=4;
}

const seek1=()=>{
  animation.value?.seek(4*750);
  progress.value=0.8;
  selected.value=0.8;
}

const seek3=()=>{
  animation.value?.seek(750);
  progress.value=0.25
  selected.value=3;
}

onMounted(()=>{
  router.beforeEach((to, _from, next) => {
    if(to.meta.music){}
    else changemusic.value.pause();
    next();
  });

  changemusic.value.volume=0.3;
 setTimeout(() => {
    changemusic.value.play();
  }, 3000);

  anime({
    targets:'.lbutton',
    duration:3000,
    opacity:[0,1],
    translateX:10,
    delay: anime.stagger(100, {start: 500}),
  }).finished;

  anime({
    targets:'.pic',
    delay:2000,
    translateY:['-60vh',0],
    duration:1500,
  }).finished;

  anime({
    targets:'.isSelected',
    opacity:[0,1],
    duration:3000,
    delay:2000
  }).finished;

 animation.value=anime.timeline({
  easing: 'easeOutExpo',
  duration: 750 ,
  autoplay:false
});

animation.value
.add({
  targets:'.lbutton:nth-child(7)',
  translateY:'45vh'
})//1

.add({
  targets:'.lbutton:nth-child(5)',
  translateY:'10vh'
},'-=750')//2

.add({
  targets:'.lbutton:nth-child(5)',
  translateY:'45vh'
})

.add({
  targets:'.lbutton:nth-child(3)',
  translateY:'20vh'//3
},'-=750')

.add({
  targets:'.lbutton:nth-child(3)',
  translateY:'45vh'
})

.add({
  targets:'.lbutton:nth-child(1)',
  translateY:'30vh'//4
},'-=750')

.finished;

})

watch(selected,(newValue)=>{
  selectmusic.value.play();
  anime({
    targets:'.black',
    opacity:[0,1],
    direction: 'alternate',
    duration:500,
    easing: 'easeInOutSine'
  }).finished
  setTimeout(() => {
    switch(newValue)
  {
    case 1:bgpic.value='bg-1';router.push('/select/1');break;
    case 2:bgpic.value='bg-2';router.push('/select/2');break;
    case 3:bgpic.value='bg-3';router.push('/select/3');break;
    case 4:bgpic.value='bg-4';router.push('/select/4');break;
  }
  }, 500);  
})

</script>

<template>
    <div class="black"></div>
    <div class="common-layout" :class="bgpic">
      <el-container>
        <el-aside width="30vw" class="left" @mousedown="onMouse" @mouseup="offMouse" @mousemove="moveMouse" @mouseleave="offMouse">
            <el-button text color="#626aef" class="lbutton" @click="seek1">简单模式</el-button><br>
            <el-button text color="#626aef" class="lbutton"@click="seek2" >困难模式</el-button><br>
            <el-button text color="#626aef" class="lbutton" @click="seek3">玩家排名</el-button><br>
            <el-button text color="#626aef" class="lbutton" @click="seek4">游戏详细</el-button><br>
            <div class="isSelected"><img src="../assets/icons/687.png" class="pic"></div>
        </el-aside>
        <el-main class="right">
          <router-view/>
        </el-main>
      </el-container>
    </div>
  </template>

<style scoped>
.bg-1 {
  background: url('../assets/icons/bgselect1.jpg') center/cover no-repeat;
}
.bg-2 {
  background: url('../assets/icons/bgselect2.jpg') center/cover no-repeat;
}
.bg-3{
  background: url('../assets/icons/bgselect3.png') center/cover no-repeat;
}
.bg-4 {
  background: url('../assets/icons/bgselect4.png') center/cover no-repeat;
}
.left{
    background: 
        linear-gradient(to right, rgb(84, 83, 82), rgba(84,82,82,0.5));
    height: 100vh;
}
.lbutton{
    margin-top: 5vh;
    margin-left: 6vw;
    font-size: 5vh;
    font-family:'ZCOOL KuaiLe', 'Hanyi Senty Candy', 'FZCuHei-B03', cursive;
}
.isSelected{
  position: absolute;
  top: 32vh;
  height: 15vh;
  width: 30vh;
  margin-left: 2vw;
  font-size: 3vw;
  border: 5px;
  border-style: solid;
  border-color: gold;
  border-radius: 5px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1), 0 1px 3px rgba(0, 0, 0, 0.08);
}
.pic{
  height: 12vh;
  margin-top: 5vh;
}
.black{
  position: absolute;
  background-color: black;
  width: 100vw;
  height: 100vh;
  opacity: 0;
  pointer-events: none;
}
</style>