#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>

typedef struct student{
	char *id;
	char *date;
	struct list_head list;
} student;
LIST_HEAD(student_list);
int simple_init(void)
  {
		student *one, *two, *three, *four, *five, *ptr;
		printk(KERN_INFO "Loading Module\n");
		one=kmalloc(sizeof(student *),GFP_KERNEL);
		two=kmalloc(sizeof(student *),GFP_KERNEL);
		three=kmalloc(sizeof(student *),GFP_KERNEL);
		four=kmalloc(sizeof(student *),GFP_KERNEL);
		five=kmalloc(sizeof(student *),GFP_KERNEL);
		one->id="106062854";
		one->date="15-7-1976";
		two->id="105062841";
		two->date="25-2-1973";
		three->id="104052142";
		three->date="3-8-1542";
		four->id="103543212";
		four->date="30-2-1912";
		five->id="101021242";
		five->date="9-2-1938";
	
		list_add_tail(&one->list, &student_list);
		list_add_tail(&two->list, &student_list);
		list_add_tail(&three->list, &student_list);
		list_add_tail(&four->list, &student_list);
		list_add_tail(&five->list, &student_list);
		//student *ptr;
		list_for_each_entry(ptr, &student_list, list)
			printk(KERN_INFO "%s, %s.\n",ptr->id,ptr->date);
		return 0;
  }

void simple_exit(void)
  {
		student *ptr, *next;
		printk(KERN_INFO "Removing Module\n");
		//student *ptr, *next;
		list_for_each_entry_safe(ptr, next, &student_list, list)
		{
			printk(KERN_INFO "Removing: %s, %s. \n",ptr->id,ptr->date);
			list_del(&ptr->list);
			kfree(ptr);
	  }
		printk(KERN_INFO "Memory freed !!\n");
  }
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module with Linked Lists");
MODULE_AUTHOR("NABA");
