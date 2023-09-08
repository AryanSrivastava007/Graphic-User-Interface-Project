from tkinter import *

import sqlite3

root = Tk()
root.title('Address Book')
root.geometry("450x600")


conn = sqlite3.connect('address_book.db')
c=conn.cursor()
'''
c.execute("""CREATE TABLE addresses (
    first_name text,
    last_name text,
    address text,
    city text,
    state text,
    zipcode integer)""")
'''

def update():
    conn = sqlite3.connect('address_book.db')
    c=conn.cursor()
    record_id = delete_box.get()

    c.execute("""UPDATE addresses SET
        first_name = :first,
        last_name = :last,
        address = :address,
        city = :city,
        state = :state,
        zipcode = :zipcode

        WHERE oid = :oid""",
        {
        'first': f_name_editor.get(),
        'last': l_name_editor.get(),
        'address': address_editor.get(),
        'city': city_editor.get(),
        'state': state_editor.get(),
        'zipcode': zipcode_editor.get(),
        'oid': record_id
        })

    conn.commit()
    conn.close()

    editor.destroy()


def edit():
    global editor
    editor = Tk()
    editor.title('Edit a Record')
    editor.geometry("450x400")

    conn = sqlite3.connect('address_book.db')
    c=conn.cursor()
    record_id = delete_box.get()

    c.execute("SELECT * FROM addresses WHERE oid = " + record_id)
    records = c.fetchall()

    global f_name_editor
    global l_name_editor
    global address_editor
    global city_editor
    global state_editor
    global zipcode_editor

    f_name_editor = Entry(editor,width=30)
    f_name_editor.grid(row=0,column=1,padx=20,pady=(10,0))

    l_name_editor = Entry(editor,width=30)
    l_name_editor.grid(row=1,column=1)

    address_editor = Entry(editor,width=30)
    address_editor.grid(row=2,column=1)

    city_editor = Entry(editor,width=30)
    city_editor.grid(row=3,column=1)

    state_editor = Entry(editor,width=30)
    state_editor.grid(row=4,column=1)

    zipcode_editor = Entry(editor,width=30)
    zipcode_editor.grid(row=5,column=1)


    f_name_label = Label(editor,text="First Name",foreground="black")
    f_name_label.grid(row=0,column=0,pady=(10,0))

    l_name_label = Label(editor,text="Last Name",foreground="black")
    l_name_label.grid(row=1,column=0)

    address_label = Label(editor,text="Address",foreground="black")
    address_label.grid(row=2,column=0)

    city_label = Label(editor,text="City",foreground="black")
    city_label.grid(row=3,column=0)

    state_label = Label(editor,text="State",foreground="black")
    state_label.grid(row=4,column=0)

    zipcode_label = Label(editor,text="Zipcode",foreground="black")
    zipcode_label.grid(row=5,column=0)

    for record in records:
        f_name_editor.insert(0,record[0])
        l_name_editor.insert(0,record[1])
        address_editor.insert(0,record[2])
        city_editor.insert(0,record[3])
        state_editor.insert(0,record[4])
        zipcode_editor.insert(0,record[5])


    edit_btn = Button(editor,text="Save Record",foreground="black",command=update)
    edit_btn.grid(row=6,column=0,columnspan=2,pady=10,ipadx=145)

    conn.commit()
    conn.close()




def delete():
    conn = sqlite3.connect('address_book.db')
    c=conn.cursor()

    c.execute("DELETE from addresses WHERE oid = " + delete_box.get())
    delete_box.delete(0,END)

    conn.commit()
    conn.close()

def submit():
    conn = sqlite3.connect('address_book.db')
    c=conn.cursor()

    c.execute("INSERT INTO addresses VALUES (:f_name, :l_name, :address, :city, :state, :zipcode)",
        {
            'f_name':f_name.get(),
            'l_name':l_name.get(),
            'address':address.get(),
            'city':city.get(),
            'state':state.get(),
            'zipcode':zipcode.get()
        }

        )

    conn.commit()
    conn.close()

    f_name.delete(0,END)
    l_name.delete(0,END)
    address.delete(0,END)
    city.delete(0,END)
    state.delete(0,END)
    zipcode.delete(0,END)



def query():
    conn = sqlite3.connect('address_book.db')
    c=conn.cursor()

    c.execute("SELECT *, oid FROM addresses")
    records = c.fetchall()
    #print(records)
    print_records = ''
    for record in records:
        print_records += str(record[6]) + " " + "\t" + str(record[0]) + " " + str(record[1]) + "\n"
    query_label = Label(root,text=print_records,foreground="black")
    query_label.grid(row=12,column=0,columnspan=2)



    conn.commit()
    conn.close()




f_name = Entry(root,width=30)
f_name.grid(row=0,column=1,padx=20,pady=(10,0))

l_name = Entry(root,width=30)
l_name.grid(row=1,column=1)

address = Entry(root,width=30)
address.grid(row=2,column=1)

city = Entry(root,width=30)
city.grid(row=3,column=1)

state = Entry(root,width=30)
state.grid(row=4,column=1)

zipcode = Entry(root,width=30)
zipcode.grid(row=5,column=1)


delete_box = Entry(root,width=30)
delete_box.grid(row=9,column=1,pady=5)



f_name_label = Label(root,text="First Name",foreground="black")
f_name_label.grid(row=0,column=0,pady=(10,0))

l_name_label = Label(root,text="Last Name",foreground="black")
l_name_label.grid(row=1,column=0)

address_label = Label(root,text="Address",foreground="black")
address_label.grid(row=2,column=0)

city_label = Label(root,text="City",foreground="black")
city_label.grid(row=3,column=0)

state_label = Label(root,text="State",foreground="black")
state_label.grid(row=4,column=0)

zipcode_label = Label(root,text="Zipcode",foreground="black")
zipcode_label.grid(row=5,column=0)

delete_box_label = Label(root,text="Select ID",foreground="black")
delete_box_label.grid(row=9,column=0,pady=5)

submit_btn = Button(root,text="Add Record To Database",foreground="black",command=submit)
submit_btn.grid(row=6,column=0,columnspan=2,pady=10,padx=10,ipadx=100)


query_btn = Button(root,text="Show Records",foreground="black",command=query)
query_btn.grid(row=7,column=0,columnspan=2,padx=10,pady=10,ipadx=137)

delete_btn = Button(root,text="Delete Record",foreground="black",command=delete)
delete_btn.grid(row=10,column=0,columnspan=2,pady=10,ipadx=136)

edit_btn = Button(root,text="Edit Record",foreground="black",command=edit)
edit_btn.grid(row=11,column=0,columnspan=2,pady=10,ipadx=143)




conn.commit()
conn.close()


root.mainloop()
