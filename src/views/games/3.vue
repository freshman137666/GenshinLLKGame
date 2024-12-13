<script setup lang="ts">
import { ref } from 'vue';


const tableData=ref([{
    name:'大伟哥',
    level:'OP-1',
    score:250
},{
    name:'门酱',
    level:'OP-1',
    score:520
},{
    name:'门酱',
    level:'OP-EX-1',
    score:520
},
{
    name:'林猪小派蒙',
    level:'OP-1',
    score:200
},{
    name:'林猪小派蒙',
    level:'OP-EX-1',
    score:100
},{
    name:'TheWord_sanqi',
    level:'OP-1',
    score:0
},
{
    name:'TheWord_sanqi',
    level:'OP-EX-1',
    score:0
}]) 

</script>

<template>
<el-table :data="tableData" style="width: 450px;margin-left: 30vw;">
    <el-table-column prop="name" label="名称" width="180" />
    <el-table-column prop="level" label="关卡" width="180" sortable />
    <el-table-column prop="score" label="得分" sortable />
  </el-table>

</template>

<style scoped>

.el-table {
    --el-table-border-color: transparent;
    --el-table-header-text-color: #000000; 
    --el-table-text-color:#000000;
    --el-table-header-bg-color: transparent;
    --el-table-bg-color: rgba(239, 143, 150,0.5);
    --el-table-tr-bg-color: transparent;
    --el-table-expanded-cell-bg-color: rgba(239, 143, 150,0.5);
}
</style>