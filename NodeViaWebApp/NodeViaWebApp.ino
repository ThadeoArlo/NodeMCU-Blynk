wifi.setmode(wifi.STATION)
-- replace with your network details
wifi.sta.config("Teddy Karhono","teddy987987")

startRead = false
gpio_0=3
gpio_2=4
gpio.mode(gpio_0, gpio.OUTPUT)
gpio.mode(gpio_2, gpio.OUTPUT)

tmr.alarm(3,20000, 1, function()
    conn = nil
    conn=net.createConnection(net.TCP, 0)
    conn:on("receive", function(conn, payload)
        startRead = false
        gpioData = ""
        for i = 1, #payload do
            c = payload:sub(i,i)
            if (c=="{") then
                startRead=true
            end
            if (startRead) then
                gpioData=gpioData..c
            end
            if (c=="}") then
                startRead=false
                t=cjson.decode(gpioData)
                for k,v in pairs(t) do
                    if (k=="gpio_0") then gpio.write(gpio_0, tonumber(v)) end
                    if (k=="gpio_2") then gpio.write(gpio_2, tonumber(v)) end
                    print(k,v)
                end
            end       
        end
    end)
    conn:connect(80,"api.homeautomationserver.com")
    conn:on("connection", function(conn, payload)
         conn:send("GET /esp8266/beta/Qj5gGVtD0icw HTTP/1.1\r\nHost: api.homeautomationserver.com\r\nConnection: keep-alive\r\nAccept: */*\r\n\r\n") end)
    conn:close()
end)
