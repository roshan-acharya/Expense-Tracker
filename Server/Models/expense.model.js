const mongoose=require('mongoose')
const ExpenseSchema=new mongoose.Schema({
    id:{
        type: String,
    },
    desc:{
        type: String,
    },
    cat:{
        type:String,
    },
    date:{
        type: Date,
    },
    amount:{
        type:Number,
    },
    wallet:{
        type:String,
    }

})
const Expense=mongoose.model("expenses",ExpenseSchema)
module.exports=Expense