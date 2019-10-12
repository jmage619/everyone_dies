function do_something()
    print("lua called!!")
    print("instantiating sprite...")
    jerry = create_sprite({name = "jerry", health = 5})
    print(sprite_get_name(jerry))
    print(sprite_get_health(jerry))
end
