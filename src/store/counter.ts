import { defineStore } from "pinia";
import { ref } from "vue";

export const useStore=defineStore('counter',()=>{
      const name =ref("");
      const password =ref("");
      const gate =ref(
        {level:"",
        score: 0 }
      )
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
    const addData=()=>{
      const existingIndex = tableData.value.findIndex(
        item => item.name === name.value && item.level === gate.value.level
      );
      if (existingIndex !== -1) {
        if(tableData.value[existingIndex].score<gate.value.score){
          tableData.value[existingIndex].score=gate.value.score;
        }
      }
      else{
        tableData.value.push({name:name.value
          ,level:gate.value.level
          ,score:gate.value.score})
      }
    }

      return{
        name,password,gate,tableData,addData
      }
})