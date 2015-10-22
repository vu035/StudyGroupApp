class StudygroupsController < ApplicationController
  before_action :set_studygroup, only: [:show, :update, :destroy]

  # GET /studygroups
  # GET /studygroups.json
  def index
    @studygroups = Studygroup.all

    render json: @studygroups
  end

  # GET /studygroups/1
  # GET /studygroups/1.json
  def show
    render json: @studygroup
  end

  # POST /studygroups
  # POST /studygroups.json
  def create
    @studygroup = Studygroup.new(studygroup_params)

    if @studygroup.save
      render json: @studygroup, status: :created, location: @studygroup
    else
      render json: @studygroup.errors, status: :unprocessable_entity
    end
  end

  # PATCH/PUT /studygroups/1
  # PATCH/PUT /studygroups/1.json
  def update
    @studygroup = Studygroup.find(params[:id])

    if @studygroup.update(studygroup_params)
      head :no_content
    else
      render json: @studygroup.errors, status: :unprocessable_entity
    end
  end

  # DELETE /studygroups/1
  # DELETE /studygroups/1.json
  def destroy
    @studygroup.destroy

    head :no_content
  end

  private

    def set_studygroup
      @studygroup = Studygroup.find(params[:id])
    end

    def studygroup_params
      params.require(:studygroup).permit(:department, :class_number)
    end
end
