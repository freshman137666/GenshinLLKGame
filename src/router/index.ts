import { createRouter,createWebHistory } from 'vue-router'
 
  const router = createRouter({
    history: createWebHistory(import.meta.env.BASE_URL),
    routes:[{path:'/',component:()=>import('../views/login.vue')},
        {path:'/select',component:()=>import('../views/select.vue'),
          children:[{path:'/select/1',component:()=>import('../views/games/1.vue'),
                     meta:{music:true},
          },
                    {path:'/select/2',component:()=>import('../views/games/2.vue'),
                      meta:{music:true},},
                      {path:'/select/3',component:()=>import('../views/games/3.vue'),
                        meta:{music:true},},
                    {path:'/select/4',component:()=>import('../views/games/4.vue'),
                        meta:{music:true},}
          ]
        },
        {path:'/ezgame',component:()=>import('../views/ezgame.vue')},
        {path:'/hdgame',component:()=>import('../views/hdgame.vue')}
    ]
  })


  export default router