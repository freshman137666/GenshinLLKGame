import { defineStore } from "pinia";
import { ref } from "vue";
import axios from "axios";

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
        score:250,
        password:'123'
    },{
        name:'门酱',
        level:'OP-1',
        score:520,
        password:'123'
    },{
        name:'门酱',
        level:'OP-EX-1',
        score:520,
        password:'123'
    },
    {
        name:'林猪小派蒙',
        level:'OP-1',
        score:200,
        password:'123'
    },{
        name:'林猪小派蒙',
        level:'OP-EX-1',
        score:100,
        password:'123'
    },{
        name:'TheWord_sanqi',
        level:'OP-1',
        score:0,
        password:'123'
    },
    {
        name:'TheWord_sanqi',
        level:'OP-EX-1',
        score:0,
        password:'123'
    }]) 

    const getData=async()=>{
        try {
            const response = await axios.post("http://localhost:11451/getUsers");
            if (response.data && Array.isArray(response.data)) {
              tableData.value = response.data; // 更新 tableData
              console.log("数据已更新:", tableData.value);
            } else {
              console.warn("返回数据格式不正确，使用默认数据");
            }
          } catch (error) {
            console.error("请求失败:", error);
          }
    }

    const sendData=async()=>{
      const newdata={
      name: name.value,
      level: gate.value.level,
      score: gate.value.score,
      password: password.value,
        }
      tableData.value.push(newdata); 


        try {
          const response=await axios.post("http://localhost:11451/sendUsers",newdata,{
                headers: {
                    "Content-Type": "application/json",
                  },
            });
            console.log("数据发送成功", response.data);
          } catch (error) {
            console.error("请求失败:", error);
          }
    }

      return{
        name,password,gate,tableData,getData,sendData
      }
})