require 'test_helper'

class StudygroupsControllerTest < ActionController::TestCase
  setup do
    @studygroup = studygroups(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:studygroups)
  end

  test "should create studygroup" do
    assert_difference('Studygroup.count') do
      post :create, studygroup: { class_number: @studygroup.class_number, department: @studygroup.department }
    end

    assert_response 201
  end

  test "should show studygroup" do
    get :show, id: @studygroup
    assert_response :success
  end

  test "should update studygroup" do
    put :update, id: @studygroup, studygroup: { class_number: @studygroup.class_number, department: @studygroup.department }
    assert_response 204
  end

  test "should destroy studygroup" do
    assert_difference('Studygroup.count', -1) do
      delete :destroy, id: @studygroup
    end

    assert_response 204
  end
end
