<script setup lang="ts">
import { onMounted,  reactive,  ref } from "vue";
import anime from "animejs";
import { useRouter } from "vue-router";
import { useStore } from "../store/counter";
import bgmusic_ from '../music/bg1.flac';
import hello_ from '../music/hellokeli.mp3';
import flower1 from '../icons/flower1.png'
import flower2 from '../icons/flower2.png'
import boom1 from '../icons/boom1.png'
import boom2 from '../icons/boom2.png'
import boom3 from '../icons/boom3.png'
import keli from '../icons/keli.png'
import backgroundImage from '../icons/login_background.png';
import { FormInstance, FormRules } from "element-plus";


const router =useRouter();
const animation = ref<anime.AnimeInstance>();
const animatline = ref<anime.AnimeTimelineInstance>();

  const dialogFormVisible = ref(false)
  const counterStore =useStore();
  const ruleFormRef = ref<FormInstance>();



  interface RuleForm{
    name:string
  }
  const rules = reactive<FormRules<RuleForm>>({
     name: [
    { required: true, message: '请输入用户名', trigger: 'blur' },
    { min: 3, max: 5, message: '最少3个字符', trigger: 'blur' },
  ],
  })
  const form = reactive<RuleForm>({
  name: "",
})

const flower=[".flo1",".flo2",".flo3",".flo4",".flo5",".flo6",".flo7",".flo8",".flo9",".flo10"];
const bgmusic=ref(new Audio(bgmusic_));
const hello=ref(new Audio(hello_));


const startgame = (formEl: FormInstance)=>{
  
  formEl.validate((valid, fields)=>{
    if(valid){
      dialogFormVisible.value = false;
      counterStore.name=form.name;
      bgmusic.value.pause();
      hello.value.pause();
      router.push('/select');
    }
    else{
      console.log('error submit!', fields)
    }
  })
}

const playbackground=()=>{
  //文字出现
animation.value=anime({
  targets:".headline",
  keyframes:[{delay:1500,
              opacity:['0','1'],},
             {
              translateY: "-35vh",
             },
             {
              scale: 1.5,
             }],
  easing: 'easeInOutQuad'
});

anime({
  targets:".txt",
  delay:2500,
  duration:4000,
  opacity:[0,1]
})

//可莉出现
anime({
  delay:2000,
  targets:'.keli',
  translateY: "-35vh",
  translateX: "-15vw",
  scale:[0,10],
  duration: 8000
})
//花花掉落
anime({
  delay:2000,
  targets:'.boom1',
  translateY: "-45vh",
  translateX: "20vw",
  scale:[0,2.5],
  rotate: '2turn',
  duration: 8000
})

anime({
  delay:2000,
  targets:'.boom2',
  translateY: "-25vh",
  translateX: "26vw",
  scale:[0,2.5],
  rotate: '1turn',
  duration: 8000
})


anime({
  delay:2000,
  targets:'.boom3',
  translateY: "-40vh",
  translateX: "5vw",
  scale:[0,2.5],
  rotate: '3turn',
  duration: 8000
})

anime({
  targets:flower,
  delay: anime.stagger(100, {start: 4000}),
  translateY: "40vh",
})
//开始按钮
anime({
  targets:'.startb',
  delay:4000,
  scale:[0,2],
  opacity:1
})
animatline.value=anime.timeline();
animatline.value.add({
  targets:'.startb',
  delay:4000,
  scale:[0,2],
  easing: 'easeOutElastic(1, .6)'
})
window.removeEventListener("click",playbackground);
}

const playmusic=()=>{
  bgmusic.value.volume=0.3;
  bgmusic.value.play().catch((error) => {
    console.error("自动播放失败:", error);
  });
  hello.value.volume=0.5;
  setTimeout(() => {
    hello.value.play();
  }, 3000);
  window.removeEventListener("click",playmusic);
}

onMounted(()=>{
  window.addEventListener("click", playmusic);
  window.addEventListener("click", playbackground);
  //背景出现
  animation.value=anime({
  targets:".main",
  opacity:['0','0.9'],
  easing: 'easeInOutQuad'
});
anime({
  targets:".headline",
  opacity:0
});
anime({
  targets:".startb",
  opacity:0
})
})


</script>

<template>
 <main>
  <div class="main" :style="{ backgroundImage: `url(${backgroundImage})` }">
    <h1 class="headline">Genshin Match</h1>
    <pre><h2 class="txt">“城里放炮，禁闭室报到<br>  炸弹伤人，琴找上门<br>  放火烧山，可莉完蛋”<br>                  ——凯亚提供的骑士团生存法则</h2></pre>
    <img :src="flower1" class="flo1">
    <img :src="flower2" class="flo2">
    <img :src="flower1" class="flo3">
    <img :src="flower2" class="flo4">
    <img :src="flower1" class="flo5">
    <img :src="flower2" class="flo6">
    <img :src="flower1" class="flo7">
    <img :src="flower2" class="flo8">
    <img :src="flower1" class="flo9">
    <img :src="flower2" class="flo10">
    <img :src="boom1" class="boom1">
    <img :src="boom2" class="boom2">
    <img :src="boom3" class="boom3">
    <img :src="keli" class="keli">
    <el-button type="warning" round class="startb" size="large" @click="dialogFormVisible =true" >点击开始游戏</el-button>
  </div>
 </main>

 <el-dialog v-model="dialogFormVisible" title="账户登录" width="500">
    <el-form :model="form" :rules="rules" ref="ruleFormRef">
      <el-form-item label="用户名" :label-width="0" prop="name">
        <el-input v-model="form.name" autocomplete="off" />
      </el-form-item>
    </el-form>
    <template #footer>
      <div class="dialog-footer">
        <el-form-item>
            <el-button type="primary" @click="startgame(ruleFormRef!)">
          登陆
            </el-button>
        </el-form-item>
      </div>
    </template>
  </el-dialog>
</template>

<style scoped>
.txt{
  position: absolute;
  font-size: 3vh;
  font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
  left: 35vw;
  top: 45vh;
  opacity: 0;
}
.startb{
  position: absolute;
  left: 45vw;
  top: 80vh;
}
.main{
  background-size: cover;
  background-position: center;
  height: 100vh;
  margin: 0;
}
.headline{
position: absolute;
left: 35vw;
top: 45vh;
font-size:45px;
color:#b7131e;
font-family:Arial, Helvetica, sans-serif;
}
.flo1{
  position: absolute;
  width: 4vw;
  left: 30vw;
  top: -10vh;
}
.flo2{
  position: absolute;
  width: 4vw;
  left: 45vw;
  top: -15vh;
}
.flo3{
  position: absolute;
  width: 4vw;
  left: 35vw;
  top: -35vh;
}
.flo4{
  position: absolute;
  width: 4vw;
  left: 29vw;
  top: -31vh;
}
.flo5{
  position: absolute;
  width: 4vw;
  left: 60vw;
  top: -27vh;
}
.flo6{
  position: absolute;
  width: 4vw;
  left: 49vw;
  top: -36vh;
}
.flo7{
  position: absolute;
  width: 4vw;
  left: 70vw;
  top: -33vh;
}
.flo8{
  position: absolute;
  width: 4vw;
  left: 63vw;
  top: -9vh;
}
.flo9{
  position: absolute;
  width: 4vw;
  left: 22vw;
  top: -31vh;
}
.flo10{
  position: absolute;
  width: 4vw;
  left: 90vw;
  top: -34vh;
}
.boom1{
  position: absolute;
  width: 4vw;
  top: 100vh;
}
.boom2{
  position: absolute;
  width: 4vw;
  top: 100vh;
}
.boom3{
  position: absolute;
  width: 4vw;
  top: 100vh;
}
.keli{
  position: absolute;
  width: 4vw;
  top: 100vh;
  left: 100vw;
}
</style>
