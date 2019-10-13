function init()
    print("init called!!")
    print("instantiating sprites...")
    table.insert(sprites, Sprite.new({name = "jerry", health = 5}))
    table.insert(sprites, Sprite.new({name = "bob", health = 3}))
    table.insert(sprites, Sprite.new({name = "joe", health = 8}))
    print("init complete")
end

function handle_damage(index)
    if Sprite.get_health(sprites[index]) == 0 then
        print(Sprite.get_name(sprites[index]) .. " has died!")
    elseif Sprite.get_health(sprites[index]) == 1 then
        print(Sprite.get_name(sprites[index]) .. " is not looking so good..")
    else
        print(Sprite.get_name(sprites[index]) .. " was damaged!")
    end
end
