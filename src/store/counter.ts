import { defineStore } from "pinia";
import { ref } from "vue";

export const useStore=defineStore('counter',()=>{
      const name =ref("");
      const password =ref("");
      const gate =ref([
        {level:"",
        score: 0 }
      ])

      return{
        name,password,gate
      }
})