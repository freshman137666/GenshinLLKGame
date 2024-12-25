<script setup lang="ts">
import skill1 from '../../assets/icons/boom.png'
import skill2 from '../../assets/icons/exchang.png'
import skill3 from '../../assets/icons/healing.png'
</script>

<template>
 <div class="block">
    <span class="demonstration">公告</span>
    <el-carousel height="50vh" motion-blur>
      <el-carousel-item style="text-align: center;">
        <el-text style="color: black; font-size: large;">
          <el-text tag="b" style="font-size: larger; color: black;">连接规则：</el-text> <br/>
          	连接的路径最多只能有两个拐弯。拐弯指的是连接路径在水平或垂直方向上的改变。<br/>
          	连接路径不能穿过其他图标。<br/>
          	连接路径的长度没有限制，但是路径上的每一段都必须是直线，且不能有交叉。<br/>
          	当两个相同的图标被选中，并且它们之间的连接符合上述规则时，这对图标就会消失。<br/><br/>
<el-text tag="b" style="font-size: large; color: black;">简单模式：</el-text><br/>
	初始时间：100秒<br/>
	每次消除增加：20秒<br/>
<el-text tag="b" style="font-size: large; color: black;">困难模式：</el-text><br/>
	初始时间：100秒<br/>
	每次消除增加：15秒<br/>
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

    <el-carousel-item style="text-align: center;">
        <el-text style="color: black; font-size: large;">
          <el-text tag="b" style="font-size: larger; color: black;">道具介绍：</el-text> <br/>
          战斗中，每个道具只能使用一次<br/>
          <el-text tag="ins" style="color: black; font-size: large;">充值可以获得更多的道具使用次数</el-text><br/>
          <el-image style="width: 50px; height: 50px" :src="skill1" :fit="'cover'" />
          <el-text tag="b" style="font-size: large; color: black;">爆裂黎明：</el-text><br/>
立刻消除一对可匹配的图片<br/>
<el-image style="width: 50px; height: 50px" :src="skill2" :fit="'cover'" />
<el-text tag="b" style="font-size: large; color: black;">生态耦合：</el-text><br/>
选择2个图片，交换位置<br/>
<el-image style="width: 50px; height: 50px" :src="skill3" :fit="'cover'" />
<el-text tag="b" style="font-size: large; color: black;">治疗强化·γ型：</el-text><br/>
立刻恢复45点生命
</el-text>

      </el-carousel-item>

    <el-carousel-item style="text-align: center;">
       <el-text style="font-size: large;">
<el-text tag="b" style="font-size: larger;">《转身提瓦特大陆成为连连看高手》制作组通讯#1期</el-text> <br/> <br/>
感谢大家游玩《转身提瓦特大陆成为连连看高手》。<br/>
以下是本次制作组为大家带来的新的一期相关内容：<br/><br/>
<el-text tag="b" style="font-size: larger;">通讯节点一</el-text> <br/>
下一次版本更新中将更新更多的关卡，为玩家带来更丰富的体验。<br/><br/>
<el-text tag="b" style="font-size: larger;">通讯节点二</el-text> <br/>
下一次版本更新中新添加道具功能，每个关卡将拥有特殊的道具，为玩家提供更多的选择<br/><br/>
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