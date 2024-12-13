<script setup lang="ts">

</script>

<template>
 <div class="block">
    <span class="demonstration">游戏说明</span>
    <el-carousel height="50vh" motion-blur>
      <el-carousel-item style="text-align: center;">
        <el-text style="color: black; font-size: large;">
          <el-text tag="b" style="font-size: larger; color: black;">连接规则：</el-text> <br/>
          	连接的路径最多只能有两个拐弯。拐弯指的是连接路径在水平或垂直方向上的改变。<br/>
          	连接路径不能穿过其他图标。<br/>
          	连接路径的长度没有限制，但是路径上的每一段都必须是直线，且不能有交叉。<br/>
          	当两个相同的图标被选中，并且它们之间的连接符合上述规则时，这对图标就会消失。<br/><br/>
<el-text tag="b" style="font-size: large; color: black;">简单模式：</el-text><br/>
	初始时间：2分钟<br/>
	每次消除增加：20秒<br/>
<el-text tag="b" style="font-size: large; color: black;">困难模式：</el-text><br/>
	初始时间：2分钟<br/>
	每次消除增加：15秒<br/>
</el-text>
      </el-carousel-item>

      <el-carousel-item style="text-align: center;">
       <el-text style="font-size: large;">
<el-text tag="b" style="font-size: larger;">冰冻道具</el-text> <br/>
功能：点击后，暂时停止计时器。<br/>
持续时间：30秒。<br/>
使用限制：每个关卡只能使用1次。<br/><br/>
<el-text tag="b" style="font-size: larger;">交换道具</el-text> <br/>
功能：允许玩家交换任意两个图案的位置，以创造匹配机会。<br/>
使用限制：每个关卡只能使用1次。<br/><br/>
<el-text tag="b" style="font-size: larger;">炸弹道具</el-text> <br/>
功能：点击后，可以随机消除一对图案。<br/>
使用限制：每个关卡只能使用1次。<br/>
       </el-text>
      </el-carousel-item>

      <el-carousel-item style="text-align: center;">
      <el-text style="font-size: large; color: black;">
        <el-text tag="b" style="font-size: larger; color: black;">积分计算细节</el-text><br/> 
每次消除的分数<br/>  
基本分数：10分/对<br/> <br/> 
连击奖励：<br/>  
2连击：额外10分<br/>  
3连击：额外30分<br/>  
4连击：额外60分<br/>  
5连击及以上：额外100分<br/> <br/> 
剩余时间的分数<br/>  
时间奖励：每剩余1秒得10分<br/>  

      </el-text>
    </el-carousel-item>

  <el-carousel-item>
  <img src="../../assets/icons/menjiang.png" alt="原神启动！">
  </el-carousel-item>

    </el-carousel>

  </div>

</template>

<style scoped>
.block{
    position: relative;
    top: 30vh;

}
.demonstration {
  color:black;
  font-size: larger;
  font-family:Verdana, Geneva, Tahoma, sans-serif;
  background-color: antiquewhite;
}
.el-carousel__item h3 {
  color: #475669;
  opacity: 0.75;
  line-height: 200px;
  margin: 0;
  text-align: center;
}

.el-carousel__item:nth-child(2n) {
  background-color: rgba(168, 243, 166, 0.8);
}

.el-carousel__item:nth-child(2n + 1) {
  background-color: rgba(206, 213, 204, 0.8);
}
</style>