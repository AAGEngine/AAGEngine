//
//  Selectable.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Selectable.h"

using namespace Adventure;

Selectable::Selectable(int numberOfitemsPerScreen, int spacing, BackgroundShape* selectedItem, Vector2i itemSize, Point2i position, std::function<void (int, Selectable*)> callback) : numberOfitemsPerScreen(numberOfitemsPerScreen), spacing(spacing), selectedItem(selectedItem), itemSize(itemSize), callback(callback){
    selectedItemIndex=0;
    this->position=position;
    this->selectedItem->setSize(itemSize.x+spacing*2, itemSize.y+spacing*2);
    
}

void Selectable::render(){
    if(items.size()==0)
        return;
    if(selectedItem!=nullptr)
        selectedItem->render();
    
    int initItem=((selectedItemIndex/numberOfitemsPerScreen)*numberOfitemsPerScreen);
    int x=position.x+spacing*2;
    
    for(int item=initItem; item<initItem+numberOfitemsPerScreen && item < items.size(); item++){
        if(selectedItemIndex==item)
            if(selectedItem!=nullptr){
                //I already added the spacing to the i
                selectedItem->setPosition(x, position.y);
                selectedItem->render();
            }
        items.at(item)->setPosition(Point2i(x+spacing, position.y+spacing));
        items.at(item)->render();
        x+=selectedItem->getSize().x+itemSize.x;
    }
    
}
void Selectable::selectOption(){
    callback(selectedItemIndex, this);
}
void Selectable::selectByMouse(Point2i clickedPosition){
    int initItem=((selectedItemIndex/numberOfitemsPerScreen)*numberOfitemsPerScreen);
    int x=position.x+spacing*2;
    
    for(int item=initItem; item<initItem+numberOfitemsPerScreen && item < items.size(); item++){
        if(clickedPosition.x >= x && clickedPosition.x <= x+itemSize.x &&
           clickedPosition.y >= position.y && clickedPosition.y <= position.y+itemSize.y)
            selectedItemIndex=item;
        x+=selectedItem->getSize().x+itemSize.x;
    }
}
void Selectable::nextItem(){
    if(selectedItemIndex<items.size()-1)
        selectedItemIndex++;
}
void Selectable::prevItem(){
    if(selectedItemIndex>0)
        selectedItemIndex--;
}

void Selectable::setNumberOfitemsPerScreen(int numberOfitemsPerScreen){
    this->numberOfitemsPerScreen=numberOfitemsPerScreen;
}
void Selectable::setSpacing(int spacing){
    this->spacing=spacing;
    this->selectedItem->setSize(itemSize.x+spacing*2, itemSize.y+spacing*2);
}
void Selectable::setSelectedShape(BackgroundShape* selectedItem){
    this->selectedItem=selectedItem;
    this->selectedItem->setSize(itemSize.x+spacing, itemSize.y+spacing);
}
void Selectable::addItem(const std::string& path){
    items.push_back(new Core::Image(path));
}

int Selectable::getNumberOfitemsPerScreen() const{
    return numberOfitemsPerScreen;
}
int Selectable::getSpacing() const{
    return spacing;
}
BackgroundShape* Selectable::getSelectedItemBackground() const{
    return selectedItem;
}
Image* Selectable::getItem(int index) const{
    if(index < items.size())
        return items.at(index);
    return nullptr;
}
vector<Image*> Selectable::getItems() const{
    return items;
}

bool Selectable::removeItem(int index){
    if(index < items.size()){
        items.erase(items.begin()+index);
        if(index==selectedItemIndex){
            if(selectedItemIndex > 0)
                selectedItemIndex--;
            else if(selectedItemIndex==0 && items.size()>0)
                selectedItemIndex++;
        }
        return true;
    }
    return false;
}