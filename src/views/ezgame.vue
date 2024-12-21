<script setup lang="ts">
import anime from 'animejs';
import { onMounted, ref, watch } from 'vue';
import bgmusic_ from '../music/ez1.flac'
import rightmusic_ from '../music/right.mp3'
import wrongmusic_ from '../music/wrong.mp3'
import endmusic_ from '../assets/music/endgame.wav'
import ezbg from '../icons/ezbg.mp4'
import tourist from '../assets/icons/avatar.png'
import axios from 'axios';
import { useRouter } from 'vue-router';
import { useStore } from '../store/counter';

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
    store.sendData();
    bgmusic.value.pause();
    centerDialogVisible.value = true
}
const returnSelect=()=>{
    centerDialogVisible.value =false;
    router.push('/select');
}
const boomvalue=ref({
    v1:'',
    v2:''
})
const isused1=ref(false);
const isused2=ref(false);
const isused3=ref(false);
const givemoney=ref(false);

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
    if(canExchange.value){
        try {
        await axios.post("http://localhost:11451/exchange",selectmessage.value);
    } catch (error) {
        console.error("Error fetching state:", error);
    }
        canExchange.value=false;
        exchange(e1,e2);
    }
    else{
        await istrue();
        if(isTrue.value){
        matchsuccess(e1,e2);
       }
        else{
        matchfaild(e1,e2);
       }
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

const useboom=async()=>{
    try {
        const response = await axios.get("http://localhost:11451/boom");
        boomvalue.value=response.data;
        console.log(boomvalue.value.v1);
        console.log(boomvalue.value.v2);
        
    } catch (error) {
        console.error("Error fetching state:", error);
    }
    const button1 = document.querySelector(`button[value="${boomvalue.value.v1}"]`) as HTMLButtonElement;
    const button2 = document.querySelector(`button[value="${boomvalue.value.v2}"]`) as HTMLButtonElement;
    matchsuccess(button1,button2);
    isused1.value=true;
}
const canExchange=ref(false);
const useExchange=()=>{
    canExchange.value=true;
    isused2.value=true;
}

const exchange=(e1:HTMLButtonElement,e2:HTMLButtonElement)=>{
    const tempClass = e1.className;
    e1.className = e2.className;
    e2.className = tempClass;
    anime({
        targets:[e1,e2],
        scale:1
    }).finished
}

const useHealing=()=>{
    hpnums.value+=45;
    isused3.value=true;
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
    <el-button class="finishgame" type="danger" round @click="endgame">点击结算</el-button>
    <el-button class="skillBoom" type="danger" :loading="isused1&&!givemoney" @click="useboom"></el-button>
    <el-button class="skillchang" type="danger" :loading="isused2&&!givemoney" @click="useExchange"></el-button>
    <div class="cheater">
        <el-switch v-model="givemoney" size="large"
        style="--el-switch-on-color: #13ce66; --el-switch-off-color: #ff4949"
        active-text="我为米哈游充过648"
        inactive-text="我没有给米哈游充值" 
        inline-prompt/></div>
    <el-button class="skillhealing" type="danger" :loading="isused3&&!givemoney" @click="useHealing"></el-button>
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
    <video :src="ezbg"  autoplay loop playsinline class="bg"></video>
    <div class="play" @click="onMouse">
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bA" value="1-1" @click="isselected"></button>
        </el-col>
            <el-col :span="3" class="cols">
                <button class="bB" value="1-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bC" value="1-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bD" value="1-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bE" value="1-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bF" value="1-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bG" value="1-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bA" value="1-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bH" value="2-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bI" value="2-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bF" value="2-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bB" value="2-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bJ" value="2-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bE" value="2-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bK" value="2-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bF" value="2-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bA" value="3-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bK" value="3-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bK" value="3-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bI" value="3-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bL" value="3-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bC" value="3-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bM" value="3-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bM" value="3-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bL" value="4-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bN" value="4-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bC" value="4-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bO" value="4-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bD" value="4-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bE" value="4-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bA" value="4-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bN" value="4-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bP" value="5-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bB" value="5-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bP" value="5-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bQ" value="5-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bG" value="5-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bF" value="5-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bL" value="5-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bR" value="5-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bN" value="6-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bJ" value="6-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bP" value="6-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bK" value="6-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bH" value="6-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bH" value="6-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bD" value="6-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bB" value="6-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bG" value="7-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bQ" value="7-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bF" value="7-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bP" value="7-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bP" value="7-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bH" value="7-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bA" value="7-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bQ" value="7-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bJ" value="8-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bO" value="8-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bM" value="8-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bF" value="8-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bR" value="8-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bE" value="8-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bD" value="8-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bO" value="8-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bC" value="9-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bO" value="9-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bN" value="9-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bP" value="9-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bC" value="9-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bM" value="9-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bI" value="9-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bR" value="9-8" @click="isselected"></button>
            </el-col>
        </el-row>
        <el-row :gutter="10" class="rows">
            <el-col :span="3" class="cols">
                <button class="bQ" value="10-1" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bJ" value="10-2" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bL" value="10-3" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bC" value="10-4" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bI" value="10-5" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bR" value="10-6" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bG" value="10-7" @click="isselected"></button>
            </el-col>
            <el-col :span="3" class="cols">
                <button class="bA" value="10-8" @click="isselected"></button>
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
.skillBoom{
    background-image: url(../assets/icons/boom.png);
    background-position: center;
    background-size: cover;
    position: absolute;
    height: 75px;
    width: 75px;
    bottom: 30px;
    left: 200px;

}
.skillchang{
    background-image: url(../assets/icons/exchang.png);
    background-position: center;
    background-size: cover;
    position: absolute;
    height: 75px;
    width: 75px;
    bottom: 30px;
    left: 300px;
}
.skillhealing{
    background-image: url(../assets/icons/healing.png);
    background-position: center;
    background-size: cover;
    position: absolute;
    height: 75px;
    width: 75px;
    bottom: 30px;
    left: 400px;
}
.cheater{
    position: absolute;
    right: 145px;
    bottom: 25px;
}
.finishgame{
    position: absolute;
    right: 30px;
    bottom: 30px;
}
.score{
    font-size: 7vw;
    color: aliceblue;
    margin-left: 20px;
    margin-top: 20px;
}
.combo{
    font-size: 3vw;
    position: absolute;
    top: 130px;
    left: 30px;
    color: #B15737;
    opacity: 0;
}
.hp{
    position: absolute;
    bottom: 24px;
    left: 25px;
}
.avatar{
    position: absolute;
    height: 130px;
    width: 130px;
    bottom: 30px;
    left: 30px;
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
    background: rgba(255, 235, 205,0.5);
    width: 48vw;
    height: 68vh;
    left: 50vw;
    top: 4vh;
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
</style>