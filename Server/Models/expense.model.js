const mongoose=require('mongoose')
const ExpenseSchema=new mongoose.Schema({
    id:{
        type: Number,
    },
    desc:{
        type: String,
    },
    cat:{
        type:String,
    },
    date:{
        type: Date,
        default: Date.now,
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