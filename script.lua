function do_something()
    print("lua called!!")
    print("instantiating sprite...")
    jerry = Sprite.new({name = "jerry", health = 5})
    print(Sprite.get_name(jerry))
    print(Sprite.get_health(jerry))
end
