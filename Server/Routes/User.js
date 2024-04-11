const express=require('express');
const router=express.Router();
const {PostUsers,CheckUsers}=require('../Controllers/user.controller')
const {postExpense,showExpense,delExpense}=require('../Controllers/expense.controller')

router.post("/user/signup", PostUsers)
router.post("/user/login", CheckUsers)
router.post("/expense/post",postExpense)
router.get("/expense/get/:id",showExpense)
router.delete("/expense/del/:id",delExpense)
module.exports=router;