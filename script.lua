function init()
    print("init called!!")
    print("instantiating sprites...")
    Sprite.new({name = "jerry", health = 5})
    Sprite.new({name = "bob", health = 3})
    Sprite.new({name = "joe", health = 8})
    print("init complete")
end

function handle_damage(sprite)
    if Sprite.get_health(sprite) == 0 then
        print(Sprite.get_name(sprite).." has died!")
    elseif Sprite.get_health(sprite) == 1 then
        print(Sprite.get_name(sprite).." is not looking so good..")
    else
        print(Sprite.get_name(sprite).." was damaged!")
    end
end
