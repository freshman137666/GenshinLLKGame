<script setup lang="ts">
import { Aim } from '@element-plus/icons-vue';
import anime from 'animejs';
import { onBeforeUnmount, onMounted, ref } from 'vue';
import router from '../../router';
import selectmusic_ from '../../music/select.wav'
import cdalao from '../../assets/icons/before.avif'
import target from '../../assets/icons/target.png'
import fgback from '../../assets/icons/hdback.png'
import dollar from '../../assets/icons/dollar.png'




const selectmusic = ref(new Audio(selectmusic_))

const startfight=()=>{
    router.push('/hdgame');
}

const select=()=>{
    selectmusic.value.play();
    anime({
        targets:'.bg',
        opacity:1,
        duration:3000
    }).finished
}

const cancel = (event: MouseEvent) => {
  const target = event.target as HTMLElement;
  if (!target.closest('.pic') && !target.closest('.bg')) {
    anime({
        targets:'.bg',
        opacity:0
    }).finished;
  }
};
onMounted(()=>{
    document.addEventListener('click', cancel);
})

onBeforeUnmount(() => {
  document.removeEventListener('click', cancel);
});
</script>

<template>
     <el-button class="pic" @click="select"></el-button>
    <div class="bg">
 <el-row :gutter="20" class="rows">
    <el-col :span="6" :offset="14" style="margin-top: 5vh;">
        <el-text style="color: aliceblue; font-size: 20px;">OP-EX-1<br/></el-text>
        <el-text tag="b" style="color: aliceblue; font-size: 40px" size="large">开放世界</el-text>
    </el-col>
 </el-row>
 <el-divider />
 <el-row style="margin-top: 5vh;">
    <el-col :span="6" :offset="14">
        <el-text style="color: crimson;">推荐等级：</el-text>
        <el-text style="color:aliceblue;">1919810</el-text>
        <el-text style="color: cornsilk;"><br/><br/>关卡描述：</el-text>
        <el-text style="color: aliceblue;">你错了，没出原神之前，多少人知道开放世界？你觉得是先知道原神再知道开放世界
            ，还是先知道开放世界才知道原神，大部分人都是前者。<el-image style="width: 20px; height: 20px;":src="cdalao"/>
    </el-text>
    </el-col>
 </el-row>
 <el-row style="margin-top: 5vh;">
    <el-col :span="6" :offset="14">
        <el-text tag="sup" style="color:aliceblue;">敌人情报</el-text>
    <el-image style="width: 100px;" :max-scale="2":zoom-rate="1.2"fit="cover" :preview-src-list="[target]" :src="target"></el-image>
    <el-text tag="sup" style="color: aliceblue;"><br/>地图</el-text>
    <el-image style="width: 100px;" :max-scale="2":zoom-rate="1.2"fit="cover" :preview-src-list="[fgback]" :src="fgback"></el-image> 
    <el-text style="color: aliceblue;"><br/>奖励<el-image style="width: 50px;" fit="cover" :src="dollar"></el-image>x50</el-text>
    </el-col>
 </el-row>
 <el-divider />
 <el-row>
    <el-col :span="6" :offset="12">
        <el-button-group class="start" style="width: 50vw;">
        <el-button type="info" disabled style="border-left-width: 50px;">没有演习</el-button>
         <el-button type="danger"style="border-right-width: 50px;" :icon="Aim" @click="startfight">开始行动</el-button>
    </el-button-group>
    </el-col>
 </el-row>
</div>
</template>

<style scoped>

.pic{
    position: absolute;
    top: 45vh;
    width: 20vw;
    left: 45vw;
    height: 20vh;
    background:url(../../assets/icons/opex1.png);
    background-size: cover;
    background-position: center;
    border: none;
    z-index: 45;
}
.bg{
    background: 
        linear-gradient(to right, rgba(84, 83, 82,0), rgba(18, 18, 18, 1));
    height: 100vh;
    opacity: 0;
}
</style>