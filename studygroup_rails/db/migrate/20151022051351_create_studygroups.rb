class CreateStudygroups < ActiveRecord::Migration
  def change
    create_table :studygroups do |t|
      t.string :department
      t.integer :class_number

      t.timestamps null: false
    end
  end
end
