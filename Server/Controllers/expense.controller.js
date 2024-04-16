const Expense=require("../Models/expense.model")

const postExpense=async(req,res)=>{
    const {id,desc,cat,date,amount,wallet}=req.body
    if (!id || !cat || !amount) {
        return res.status(422).json({ error: "Credentials must be filled" });
      }
    else{
        try{
            const data=await Expense.create(req.body);
            return res.status(200).json({id:data._id,message:"Added"})
         }
         catch(e){
            console.log(e);
         }
        }
    }
const showExpense=async(req,res)=>{
    try{
        const id=req.params.id
        const data=await Expense.find({id:req.params.id})
        if (!data) {
            return res.status(404).json({ message: 'Expense not found' });
        }
        return res.json(data); 
    }
    catch(e){
        return res.json(e)
    }
}
const delExpense=async(req,res)=>{
    try{
        if(req.params.id){
            const del = await Expense.findByIdAndDelete(req.params.id);
           return res.json(del).status(200);
        }
    }
    catch(e){
        return res.json(e);
    }
}
const UpdateExpense = async (req, res) => {
    try {
      const id = req.params.id;
      const update = await Expense.findByIdAndUpdate(id, req.body);
      res.send(update);
    } catch (e) {
          res.json(e);
    }
  };
module.exports={
    postExpense,
    showExpense,
    delExpense,
    UpdateExpense
}