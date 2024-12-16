<script setup lang="ts">
import { ref } from 'vue';
import { useStore } from '../../store/counter';

const store=useStore();

const tableData=store.tableData;

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